
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include"Sqlite.h"






/**
 * @description: 具有处理缓存缺失的作用
 * @param {Pager} *pager
 * @param {uint32_t} page_num
 * @return {*}
 * @note: 
 */
void *get_page(Pager *pager, uint32_t page_num)
{
    if (page_num > TABLE_MAX_PAGES)
    {
        printf("Tried to fetch page number out of bounds. %d > %d\n", page_num, TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }
    if (pager->pages[page_num] == NULL)
    {
        // 缓存缺失，分配内存并加载文件
        void *page = malloc(PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        // 可以在文件末尾保存部分页面
        if (pager->file_length % PAGE_SIZE)
        {
            num_pages += 1;
        }

        if (page_num <= num_pages)
        {
            lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if (bytes_read == -1)
            {
                printf("Error reading file:%d\n", errno);
                exit(EXIT_FAILURE);
            }
        }
        pager->pages[page_num] = page;
        if (page_num >= pager->num_pages)
        {
            pager->num_pages = page_num + 1;
        }
    }
    return pager->pages[page_num];
}

/**
 * @description: 根据指定文件名打开文件，并初始化
 * @param {char} *filename
 * @return {*}
 * @note: // S_IWUSR |	  S_IRUSR
 */
Pager *pager_open(const char *filename)
{
    int fd = open(filename,
                  O_RDWR |
                      O_CREAT);
    if (fd == -1)
    {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }
    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager *pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;

    pager->num_pages = (file_length / PAGE_SIZE);

    if (file_length % PAGE_SIZE != 0)
    {
        printf("Db file is not a whole number of pages. Corrupt file.\n");
        exit(EXIT_FAILURE);
    }

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pager->pages[i] = NULL;
    }
    return pager;
}

/**
 * @description: 
 * @param {Pager} *pager
 * @param {uint32_t} page_num
 * @return {*}
 * @note: 
 */
void pager_flush(Pager *pager, uint32_t page_num)
{
    if (pager->pages[page_num] == NULL)
    {
        printf("Tried to flush null page.\n");
        exit(EXIT_FAILURE);
    }
    off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
    if (offset == -1)
    {
        printf("Error seeking: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_writen = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);

    if (bytes_writen == -1)
    {
        printf("Error writing : %d\n", errno);
        exit(EXIT_FAILURE);
    }
}



/**
 * @description: 打开数据库
 * @param {char} *filename
 * @return {*}
 * @note: 
 */
Table *db_open(const char *filename)
{
    Pager *pager = pager_open(filename);

    Table *table = malloc(sizeof(Table));
    table->pager = pager;
    table->root_page_num = 0;

    if (pager->num_pages == 0)
    {
        void *root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
        set_node_root(root_node, true);
    }
    return table;
}



/**
 * @description: 关闭数据库
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
void db_close(Table *table)
{
    Pager *pager = table->pager;
    for (uint32_t i = 0; i < pager->num_pages; i++)
    {
        if (pager->pages[i] == NULL)
        {
            continue;
        }

        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }
    int result = close(pager->file_descriptor);
    if (result == -1)
    {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        void *page = pager->pages[i];
        if (page)
        {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}

/**
 * @description: 除非我们开始回收空闲页面，否则总会有新的页面转到数据库文件的末尾?
 * @param {Pager} *Pager
 * @return {*}
 * @note: 
 */
uint32_t get_unused_page_num(Pager *Pager)
{
    return Pager->num_pages;
}
