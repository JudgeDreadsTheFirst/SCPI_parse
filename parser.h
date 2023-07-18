
#ifndef SCPI_PARSE_PARSER_H
#define SCPI_PARSE_PARSER_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CHILD 5 // максимальное кол-во детей узла в дереве команд
//#define NUM_NODES 25
#define NUM_ROOTS 5 // максимальное кол-во корневых узлов в дереве команд
#define NUM_BASIC_CMD 3

/*
@brief:
@note:
@param:
*/
enum _scpi_res_t{
    RES_OK = 0,
    RES_ERROR = 1
};

enum _scpi_types_t{
    SCPI_DOUBLE,
    SCPI_BOOL,
    SCPI_INT,
    SCPI_STR
};

typedef enum _scpi_types_t scpi_types;
typedef enum _scpi_res_t scpi_res_t;

typedef scpi_res_t (*comm_cb_t)(char *str);
typedef scpi_res_t (*intf_cb_t)(char *str);

struct _scpi_cmd_t{
    const char *keyword;
    comm_cb_t callback;
};
typedef struct _scpi_cmd_t scpi_cmd_t;

struct _scpi_param_t{
    const char *param;
    scpi_types type;
};
typedef struct _scpi_param_t scpi_param_t;

typedef struct _scpi_cmd_node scpi_cmd_node;
struct _scpi_cmd_node{
    scpi_cmd_t cmd;
    int num_child;
    scpi_cmd_node *childs[NUM_CHILD];
};


struct _scpi_basic_cmd{
    int num_cmd;
    scpi_cmd_t cmd[NUM_BASIC_CMD];
};
typedef struct _scpi_basic_cmd scpi_basic_cmd;

struct _scpi_comm_intf{
    intf_cb_t write;
    intf_cb_t read;
    intf_cb_t reset;
};
typedef struct _scpi_comm_intf scpi_comm_intf;

struct _scpi_dev{
    int num_nodes;
    scpi_comm_intf *interface;
    scpi_cmd_node *root[NUM_ROOTS];
};
typedef struct _scpi_dev scpi_dev;

void print_tokens(char *str);

scpi_cmd_node *init_node(scpi_cmd_t cmd, int num);
void process_tree(scpi_cmd_node *root,char *cmd);
void choose_root(scpi_dev *dev,char *cmd);

scpi_res_t debug_callback(char *keyword);
scpi_res_t debug_query_callback(char *keyword);

#endif //SCPI_PARSE_PARSER_H
