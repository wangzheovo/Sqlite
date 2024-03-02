/*
 * @Author: WangZhe
 * @Date: 2023-09-07 21:30:45
 * @LastEditors: WangZhe
 * @LastEditTime: 2023-09-13 21:32:44
 * @FilePath: /Sqlite/Cursor.c
 * @Description: 数据库游标
 */

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
 * @description: 返回给定关键字的位置，如果关键字不存在，则返回应该插入的位置
 * @param {Table} *table
 * @param {uint32_t} key
 * @return {*}
 * @note: 
 */
Cursor *table_find(Table *table, uint32_t key)
{
    uint32_t root_page_num = table->root_page_num;
    void *root_node = get_page(table->pager, root_page_num);
    if (get_node_type(root_node) == NODE_LEAF)
    {
        return leaf_node_find(table, root_page_num, key);
    }
    else
    {
        return internal_node_find(table, root_page_num, key);
    }
}


/**
 * @description: 
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
Cursor *table_start(Table *table)
{
    Cursor *cursor = table_find(table, 0);

    void *node = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);
    cursor->end_of_table = (num_cells == 0);

    return cursor;
}



/**
 * @description: 移动游标
 * @param {Cursor} *cursor
 * @return {*}
 * @note: 
 */
void cursor_advance(Cursor *cursor)
{
    uint32_t page_num = cursor->page_num;
    void *node = get_page(cursor->table->pager, page_num);

    cursor->cell_num += 1;
    if (cursor->cell_num >= (*leaf_node_num_cells(node)))
    {
        uint32_t next_page_num = *leaf_node_next_leaf(node);
        if (next_page_num == 0)
        {
            cursor->end_of_table = true;
        }
        else
        {
            cursor->page_num = next_page_num;
            cursor->cell_num = 0;
        }
    }
}


/**
 * @description: 根据特定的行确定是在哪一页进行读/写操作
 * @param {Cursor} *cursor
 * @return {*}
 * @note: 
 */
void *cursor_value(Cursor *cursor)
{
    uint32_t page_num = cursor->page_num;
    void *page = get_page(cursor->table->pager, page_num);

    return leaf_node_value(page, cursor->cell_num);
}