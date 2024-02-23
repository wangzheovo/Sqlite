# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# 项目信息
project (SQLite)


# 指定生成目标
add_executable(SQLite main.c Constants.c REPL.c SQLCompiler.c Pager.c BTree.c Table.c Cursor.c)

set_target_properties(SQLite PROPERTIES OUTPUT_NAME "db")