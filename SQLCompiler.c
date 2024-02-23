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

    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
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

    }
    return EXECUTE_SUCCESS;
}

