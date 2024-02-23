#ifndef SQLITE_H
#define SQLITE_H

/**
 * REPL_H
*/

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;


/**
 * TABLE_H
*/

const extern uint32_t PAGE_SIZE;
#define TABLE_MAX_PAGES 100

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

/**
 * PAGER_H
*/

#define INVALID_PAGE_NUM UINT32_MAX


typedef struct
{
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;


typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;



typedef struct
{
    uint32_t root_page_num;
    Pager *pager;
} Table;



/**
 * SQLCOMPILIER_H
*/

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY
} ExecuteResult;


typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;




const extern uint32_t ID_SIZE;
const extern uint32_t USERNAME_SIZE;
const extern uint32_t EMAIL_SIZE;
const extern uint32_t ID_OFFSET;
const extern uint32_t USERNAME_OFFSET;
const extern uint32_t EMAIL_OFFSET;
const extern uint32_t ROW_SIZE;


typedef struct
{
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;



InputBuffer *new_input_buffer();

void print_prompt();

void read_input(InputBuffer *input_buffer);

void close_input_buffer(InputBuffer *input_buffer);

ExecuteResult execute_insert(Statement *statement, Table *table);

ExecuteResult execute_select(Statement *statement, Table *table);

void serialize_row(Row *source, void *destination);

void deserialize_row(void *source, Row *destination);

void print_row(Row *row);

void *get_page(Pager *pager, uint32_t page_num);

Pager *pager_open(const char *filename);

void pager_flush(Pager *pager, uint32_t page_num);

Table *db_open(const char *filename);

void db_close(Table *table);

uint32_t get_unused_page_num(Pager *Pager);

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);

PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement);

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

ExecuteResult execute_statement(Statement *statement, Table *table);

Cursor *table_find(Table *table, uint32_t key);

Cursor *table_start(Table *table);

void cursor_advance(Cursor *cursor);

void *cursor_value(Cursor *cursor);



/**
 * BTREE_H
*/


const extern uint32_t NODE_TYPE_SIZE;
const extern uint32_t NODE_TYPE_OFFSET;
const extern uint32_t IS_ROOT_SIZE;
const extern uint32_t IS_ROOT_OFFSET;
const extern uint32_t PARENT_POINTER_SIZE;
const extern uint32_t PARENT_POINTER_OFFSET;
const extern uint8_t COMMON_NODE_HEADER_SIZE;


const extern uint32_t LEAF_NODE_NUM_CELLS_SIZE;
const extern uint32_t LEAF_NODE_NUM_CELLS_OFFSET;
const extern uint32_t LEAF_NODE_NEXT_LEAF_SIZE;
const extern uint32_t LEAF_NODE_NEXT_LEAF_OFFSET;
const extern uint32_t LEAF_NODE_HEADER_SIZE;


const extern uint32_t LEAF_NODE_KEY_SIZE;
const extern uint32_t LEAF_NODE_KEY_OFFSET;
const extern uint32_t LEAF_NODE_VALUE_SIZE;
const extern uint32_t LEAF_NODE_VALUE_OFFSET;
const extern uint32_t LEAF_NODE_CELL_SIZE;
const extern uint32_t LEAF_NODE_SPACE_FOR_CELLS;
const extern uint32_t LEAF_NODE_MAX_CELLS;


const extern uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT;
const extern uint32_t LEAF_NODE_LEFT_SPLIT_COUNT;


const extern uint32_t INTERNAL_NODE_NUM_KEYS_SIZE;
const extern uint32_t INTERNAL_NODE_NUM_KEYS_OFFSET;
const extern uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE;
const extern uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET;
const extern uint32_t INTERNAL_NODE_HEADER_SIZE;



const extern uint32_t INTERNAL_NODE_KEY_SIZE;
const extern uint32_t INTERNAL_NODE_CHILD_SIZE;
const extern uint32_t INTERNAL_NODE_CELL_SIZE;


const extern uint32_t INTERNAL_NODE_MAX_CELLS;


typedef enum
{
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

void indent(uint32_t level);

void print_tree(Pager *pager, uint32_t page_num, uint32_t indentation_level);

void print_constants();

uint32_t *leaf_node_num_cells(void *node);

void *leaf_node_cell(void *node, uint32_t cell_num);

uint32_t *leaf_node_key(void *node, uint32_t cell_num);

void *leaf_node_value(void *node, uint32_t cell_num);

uint32_t *leaf_node_next_leaf(void *node);

NodeType get_node_type(void *node);

void set_node_type(void *node, NodeType type);

bool is_node_root(void *node);

void set_node_root(void *node, bool is_root);

void initialize_leaf_node(void* node);

uint32_t* internal_node_right_child(void* node);

void initialize_internal_node(void* node);

uint32_t *internal_node_num_keys(void *node);

uint32_t *internal_node_cell(void *node, uint32_t cell_num);

uint32_t *internal_node_child(void *node, uint32_t child_num);

uint32_t *internal_node_key(void *node, uint32_t key_num);

uint32_t get_node_max_key(Pager *pager, void *node);

uint32_t *node_parent(void *node);

void create_new_root(Table *table, uint32_t right_child_page_num);

void update_internal_node_key(void *node, uint32_t old_key, uint32_t new_key);

void internal_node_split_and_insert(Table *table, uint32_t parent_page_num,
                                    uint32_t child_page_num);

void internal_node_insert(Table *table, uint32_t parent_page_num, uint32_t child_page_num);

void leaf_node_split_and_insert(Cursor *cursor, uint32_t key, Row *value);

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);

Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key);

uint32_t internal_node_find_child(void *node, uint32_t key);

Cursor *internal_node_find(Table *table, uint32_t page_num, uint32_t key);


#endif