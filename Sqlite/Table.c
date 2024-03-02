/*
 * @Author: WangZhe
 * @Date: 2023-09-07 20:57:58
 * @LastEditors: WangZhe
 * @LastEditTime: 2023-09-09 21:21:40
 * @FilePath: /Sqlite/Table.c
 * @Description: 
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
 * @description: 紧凑结构转换,将数据紧凑存储在连续的字节上
 * @param {Row} *source
 * @param {void} *destination
 * @return {*}
 * @note: 
 */
void serialize_row(Row *source, void *destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    strncpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);
    strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

/**
 * @description: 从内存中读取并存入表结构Row中
 * @param {void} *source
 * @param {Row} *destination
 * @return {*}
 * @note: 
 */
void deserialize_row(void *source, Row *destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}



/**
 * @description: 执行插入操作
 * @param {Table} *table
 * @param {uint32_t} key
 * @return {*}
 * @note: 
 */
ExecuteResult execute_insert(Statement *statement, Table *table)
{
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = (*leaf_node_num_cells(node));

    Row *row_to_insert = &(statement->row_to_insert);
    uint32_t key_to_insert = row_to_insert->id;
    Cursor *cursor = table_find(table, key_to_insert);

    if (cursor->cell_num < num_cells)
    {
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        if (key_at_index == key_to_insert)
        {
            return EXECUTE_DUPLICATE_KEY;
        }
    }

    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

    free(cursor);
    return EXECUTE_SUCCESS;
}

/**
 * @description: 执行查询操作
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
ExecuteResult execute_select(Statement *statement, Table *table)
{
    Cursor *cursor = table_start(table);
    Row row;
    while (!(cursor->end_of_table))
    {
        deserialize_row(cursor_value(cursor), &row);
        if(row.id == statement->row_to_select.select_id || statement->row_to_select.select_id == -1){
            print_row(&row);
        }
        cursor_advance(cursor);
    }
    free(cursor);
    return EXECUTE_SUCCESS;
}

/**
 * @description: 执行更新操作
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
ExecuteResult execute_update(Statement *statement, Table *table)
{
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = (*leaf_node_num_cells(node));

    Row *row_to_update = &(statement->row_to_update);
    uint32_t key_to_update = row_to_update->update_id;
    Cursor *cursor = table_find(table, key_to_update);

    if (cursor->cell_num < num_cells)
    {
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        // printf("key_to_update: %d,key_at_index : %d\n",key_to_update, key_at_index);
        if (key_at_index == key_to_update)
        {
            leaf_node_update(cursor, row_to_update->update_id, row_to_update);
            free(cursor);
            return EXECUTE_SUCCESS;
        }
    }
    free(cursor);
    return EXECUTE_KEY_NONE;
}



/**
 * @description: 执行删除
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
ExecuteResult execute_delete(Statement *statement, Table *table)
{
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = (*leaf_node_num_cells(node));
    if (num_cells <= 0) {
        return EXECUTE_TABLE_EMPTY;
    }
    Row *row_to_delete = &(statement->row_to_delete);
    uint32_t key_to_delete = row_to_delete->delete_id;
    Cursor *cursor = table_find(table, key_to_delete);

    if (cursor->cell_num < num_cells)
    {
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        // printf("key at index : %d, key to delete: %d\n",key_at_index, key_to_delete);
        if (key_at_index == key_to_delete)
        {
            leaf_node_delete(cursor, row_to_delete->id, row_to_delete);
            free(cursor);
            return EXECUTE_SUCCESS;
            
        }
    }

    free(cursor);
    return EXECUTE_KEY_NONE;
}



/**
 * @description: 输出行
 * @param {Row} *row
 * @return {*}
 * @note: 
 */
void print_row(Row *row)
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
