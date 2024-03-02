/*
 * @Author: WangZhe
 * @Date: 2023-09-07 20:38:35
 * @LastEditors: WangZhe
 * @LastEditTime: 2023-09-13 21:37:23
 * @FilePath: /Sqlite/SQLCompiler.c
 * @Description: SQL语句编译识别，并交由虚拟机执行
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
 * @description: 判断是否是元命令
 * @param {InputBuffer} *input_buffer
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        close_input_buffer(input_buffer);
        db_close(table);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(input_buffer->buffer, ".constants") == 0)
    {
        printf("Constants:\n");
        print_constants();
        return META_COMMAND_SUCCESS;
    }
    else if (strcmp(input_buffer->buffer, ".btree") == 0)
    {
        printf("Tree:\n");
        print_tree(table->pager, 0, 0);
        return META_COMMAND_SUCCESS;
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}


/**
 * @description: 插入操作前的判断
 * @param {InputBuffer} *input_buffer
 * @param {Statement} *statement
 * @return {*}
 * @note: 
 */
PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_INSERT;

    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    int id = atoi(id_string);
    if (id < 0)
    {
        return PREPARE_NEGATIVE_ID;
    }
    if (strlen(username) > COLUMN_USERNAME_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(email) > COLUMN_EMAIL_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

PrepareResult prepare_select(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_SELECT;
    
    if(strcmp(input_buffer->buffer, "select") == 0){
        int select_id = -1;
        statement->row_to_select.select_id = select_id;
        return PREPARE_SUCCESS;
    }

    char *keyword = strtok(input_buffer->buffer, " ");
    char *where_key = strtok(NULL, " ");
    char *select_id_string = strtok(NULL, " ");
    
    if ( strcmp(where_key,"where")!=0 && where_key != NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    int select_id = -1;
    if(select_id_string != NULL){
        select_id = atoi(select_id_string);
    }
    statement->row_to_select.select_id = select_id;
    
    return PREPARE_SUCCESS;
}

PrepareResult prepare_update(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_UPDATE;
    
    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");
    char *where_key = strtok(NULL, " ");
    // char *id_key = strtok(NULL, " ");
    char *update_id_string = strtok(NULL, " ");
    
    if (id_string == NULL || username == NULL || email == NULL || strcmp(where_key,"where")!=0)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    int id = atoi(id_string);
    int update_id = atoi(update_id_string);
    if (id < 0 || update_id < 0)
    {
        return PREPARE_NEGATIVE_ID;
    }
    if (strlen(username) > COLUMN_USERNAME_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(email) > COLUMN_EMAIL_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    statement->row_to_update.id = id;
    strcpy(statement->row_to_update.username, username);
    strcpy(statement->row_to_update.email, email);
    statement->row_to_update.update_id = update_id;
    
    
    return PREPARE_SUCCESS;
}

PrepareResult prepare_delete(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_DELETE;

    char *keyword = strtok(input_buffer->buffer, " ");
    char *where_key = strtok(NULL, " ");
    char *delete_id_string = strtok(NULL, " ");
    
    if ( strcmp(where_key,"where")!=0 || where_key == NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    
    int delete_id = atoi(delete_id_string);
    
    statement->row_to_delete.delete_id = delete_id;
    return PREPARE_SUCCESS;
}


/**
 * @description: 识别输入语句的类型
 * @param {InputBuffer*} input_buffer
 * @param {Statement*} statement
 * @return {*}
 */
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement)
{
    //
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        return prepare_insert(input_buffer, statement);
    }

    if (strncmp(input_buffer->buffer, "select", 6) == 0)
    {
        return prepare_select(input_buffer,statement);
    }
    if(strncmp(input_buffer->buffer, "update", 6) == 0)
    {
        return prepare_update(input_buffer, statement);
    }
    if(strncmp(input_buffer->buffer, "delete", 6) == 0)
    {
        return prepare_delete(input_buffer, statement);
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}


/**
 * @description: 根据输入语句的类型执行相应的操作
 * @param {Statement} *statement
 * @param {Table} *table
 * @return {*}
 * @note: 
 */
ExecuteResult execute_statement(Statement *statement, Table *table)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        return execute_insert(statement, table);
    case (STATEMENT_SELECT):
        return execute_select(statement, table);
    case (STATEMENT_UPDATE):
        return execute_update(statement, table);
    case (STATEMENT_DELETE):
        return execute_delete(statement, table);

    }
    return EXECUTE_SUCCESS;
}

