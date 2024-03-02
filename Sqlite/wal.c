#include"Sqlite.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define u32 uint32_t
#define HASHTABLE_NPAGE      4096                 /* Must be power of 2 */
#define HASHTABLE_HASH_1     383                  /* 计算hash值的一个参数Should be prime */
#define HASHTABLE_NSLOT      (HASHTABLE_NPAGE*2)  /*即8192 Must be a power of 2 */
//第一页的数量，即4062
#define HASHTABLE_NPAGE_ONE  (HASHTABLE_NPAGE - (WALINDEX_HDR_SIZE/sizeof(u32)))



int walFramePage(u32 iFrame){
  int iHash = (iFrame+HASHTABLE_NPAGE-HASHTABLE_NPAGE_ONE-1) / HASHTABLE_NPAGE;
  return iHash;
}

static int walHashGet(
  Wal *pWal,                      /* WAL handle */
  int iHash,                      /* Find the iHash'th table */
  volatile ht_slot **paHash,      /* OUT: Pointer to hash index */
  volatile u32 **paPgno,          /* OUT: Pointer to page number array */
  u32 *piZero                     /* OUT: Frame associated with *paPgno[0] */
){
  int rc;                         /* Return code */
  volatile u32 *aPgno;
  //获取WAL-index中的第iHash页地址放在aPgno
  rc = walIndexPage(pWal, iHash, &aPgno);
  assert( rc==SQLITE_OK || iHash>0 );
 
  if( rc==SQLITE_OK ){
    u32 iZero;
    volatile ht_slot *aHash;
    //将第aPgno[4096]的地址用作hash表
    aHash = (volatile ht_slot *)&aPgno[HASHTABLE_NPAGE];
    if( iHash==0 ){
      //第一页的aPgno去掉文件头136字节
      aPgno = &aPgno[WALINDEX_HDR_SIZE/sizeof(u32)];
      iZero = 0;
    }else{
      iZero = HASHTABLE_NPAGE_ONE + (iHash-1)*HASHTABLE_NPAGE;
    }
    // 将aPgno的第一个元素改为从1开始，paPgno[1]即aPgno[0]
    *paPgno = &aPgno[-1];
    *paHash = aHash;
    *piZero = iZero;
  }
  return rc;
}


static int walIndexAppend(Wal *pWal, u32 iFrame, u32 iPage){
  int rc;                         /* Return code */
  u32 iZero = 0;                  /* One less than frame number of aPgno[1] */
  volatile u32 *aPgno = 0;        /* Page number array */
  volatile ht_slot *aHash = 0;    /* Hash table */
 
  rc = walHashGet(pWal, walFramePage(iFrame), &aHash, &aPgno, &iZero);
 
  /* Assuming the wal-index file was successfully mapped, populate the
  ** page number array and hash table entry.
  */
  if( rc==SQLITE_OK ){
    int iKey;                     /* Hash table key */
    int idx;                      /* Value to write to hash-table slot */
    int nCollide;                 /* Number of hash collisions */
    //第iFrame帧对应aPgno[idx]
    idx = iFrame - iZero;
    assert( idx <= HASHTABLE_NSLOT/2 + 1 );
 
    /* If the entry in aPgno[] is already set, then the previous writer
    ** must have exited unexpectedly in the middle of a transaction (after
    ** writing one or more dirty pages to the WAL to free up memory). 
    ** Remove the remnants of that writers uncommitted transaction from 
    ** the hash-table before writing any new entries.
    */
    //因为WAL的帧是按照顺序添加到aPgno，事务提交后会
    //更新WAL的最大帧索引mxFrame，所以如果此时向hash表
    //添加元素时aPgno[idx]已经存在，说明之前出现事务失败
    if( aPgno[idx] ){
      //清除aHash中记录的索引大于mxFrame的元素
      walCleanupHash(pWal);
      assert( !aPgno[idx] );
    }
    /* Write the aPgno[] array entry and the hash-table slot. */
    //冲突后把iKey加1即可，hash表中之前写入了idx个元素
    //所以冲突最多发生idx次
    nCollide = idx;
    for(iKey=walHash(iPage); aHash[iKey]; iKey=walNextHash(iKey)){
      if( (nCollide--)==0 ) return SQLITE_CORRUPT_BKPT;
    }
    //写入页号
    aPgno[idx] = iPage;
    //写入索引
    aHash[iKey] = (ht_slot)idx;
  }
  return rc;
}

//要查找的页号为pgno
int sqlite3WalFindFrame(
  Wal *pWal,                      /* WAL handle */
  Pgno pgno,                      /* Database page number to read data for */
  u32 *piRead                     /* OUT: Frame number (or zero) */
){
  u32 iRead = 0;                  /* If !=0, WAL frame to return data from */
  //查找的最大帧索引
  u32 iLast = pWal->hdr.mxFrame;  /* Last page in WAL for this reader */
  int iHash;                      /* Used to loop through N hash tables */
  int iMinHash;
  //限定查找的最小帧
  iMinHash = walFramePage(pWal->minFrame);
  for(iHash=walFramePage(iLast); iHash>=iMinHash && iRead==0; iHash--){
    volatile ht_slot *aHash;      /* Pointer to hash table */
    volatile u32 *aPgno;          /* Pointer to array of page numbers */
    u32 iZero;                    /* Frame number corresponding to aPgno[0] */
    int iKey;                     /* Hash slot index */
    int nCollide;                 /* Number of hash collisions remaining */
    int rc;                       /* Error code */
    //获取WAL-index中的第iHash页
    rc = walHashGet(pWal, iHash, &aHash, &aPgno, &iZero);
    if( rc!=SQLITE_OK ){
      return rc;
    }
    //最大冲突次数8192次
    //其实4096就够了，aPgno中最多4096个元素
    nCollide = HASHTABLE_NSLOT;
    //把pgno映射成对应的hash值key 
    //冲突后继续查找，直到aHash[iKey]为0
    for(iKey=walHash(pgno); aHash[iKey]; iKey=walNextHash(iKey)){
      //aHash[iKey]存的是iFrame在aPgno中对应的索引，将其还原
      u32 iFrame = aHash[iKey] + iZero;
      // iFrame对应的aPgno元素存的页号是pgno说明找到
      if( iFrame<=iLast && iFrame>=pWal->minFrame && aPgno[aHash[iKey]]==pgno ){
        //返回要找的帧号
        iRead = iFrame;
      }
      if( (nCollide--)==0 ){
        return SQLITE_CORRUPT_BKPT;
      }
    }
  }
  *piRead = iRead;
  return SQLITE_OK;
}