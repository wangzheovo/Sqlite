/*
 * @Author: WangZhe
 * @Date: 2023-09-07 19:56:17
 * @LastEditors: WangZhe
 * @LastEditTime: 2023-09-09 21:23:46
 * @FilePath: /Sqlite/REPL.c
 * @Description: 交互式顶层构件
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
 * @description: 输入缓冲区初始化
 * @return {*}
 * @note:
 */
InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}


/**
 * @description: 输入提示
 * @return {*}
 * @note: 
 */
void print_prompt()
{
    printf("db > ");
}


/**
 * @description: 输入缓冲区
 * @param {InputBuffer} *input_buffer
 * @return {*}
 * @note: 
 */
void read_input(InputBuffer *input_buffer)
{

    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    //?
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}


/**
 * @description: 释放缓冲区
 * @param {InputBuffer} *input_buffer
 * @return {*}
 * @note: 
 */
void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}
