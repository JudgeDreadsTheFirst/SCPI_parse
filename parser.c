
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*
 * @brief: function to visualize tokens
 * @param str: string to break into tokens
 */
void print_tokens(char *str){
    printf("Parse started\r\n");
    char *tok = strtok(str,":");

    while(tok){
        printf("token: %s\r\n",tok);
        tok = strtok(NULL,":");

    }

}
/*
 * @brief: plug for callbacks, prints it input string
 * @param keyword: string to print
 * @retval: always returns RES_OK
 */
scpi_res_t debug_callback(char *keyword){
    printf("callback called for %s keyword\r\n",keyword);
    return RES_OK;
}

/*
 * @brief: node initializer
 * @note: inits nodes parameters, pointers to child initialized with NULL, further if needed they
 * must got value from other function
 * @param cmd: input pair of command keyword and callback function
 * @param num: number of this node child nodes, needed to reduce compares
 * in further funcs
 * @retval: returns node
 */
scpi_cmd_node *init_node(scpi_cmd_t cmd, int num){
    scpi_cmd_node *res = malloc(sizeof(scpi_cmd_node));
    if(res!=NULL){
        res->cmd = cmd;
        res->num_child = num;
        for(int i=0;i< NUM_CHILD;i++){
            res->childs[i] = NULL;
        }
    }
    return res;
}
/*
 * @brief: recursive tree processing function
 * @param root: 'root' node or other node from further iterations
 * needed to check keywords
 */
void process_tree(scpi_cmd_node *root,char *cmd){
    char *tkn = NULL;
    const char *res = NULL;
    if((res=strchr(cmd,':')) != NULL){
        tkn = strtok(cmd,":");
        printf("Got %s token from %s string.\r\n",tkn,cmd);
        for(int i =0;i < root->num_child;i++){
            if(strcmp(root->childs[i]->cmd.keyword,tkn) == 0){
                process_tree(root->childs[i], ++res);
                break;
            }
        }
    }else{
        if(strchr(cmd,'?') != NULL){
            tkn = strtok(cmd,  "?");
            printf("Got %s token from %s string.\r\n",tkn,cmd);
            for(int i =0;i < root->num_child;i++) {
                if (strcmp(root->childs[i]->cmd.keyword, tkn) == 0) {
                    root->childs[i]->cmd.callback(tkn);
                    break;
                }
            }
            return;
        }else{
            tkn = strtok(cmd,  " ");
            printf("Got %s token from %s string.\r\n",tkn,cmd);
            for(int i =0;i < root->num_child;i++) {
                if (strcmp(root->childs[i]->cmd.keyword, tkn) == 0) {
                    root->childs[i]->cmd.callback(tkn);
                    break;
                }
            }
            return;
        }
        return;
    }
}
/*
 * @brief: func needed to choose which tree to process by comparing it roots to
 * cmd start
 */
void choose_root(scpi_dev *dev,char *cmd){
    printf("started %s func\r\n",__func__);
    char *tkn = NULL;
    const char *res = NULL;
    //const char *res;
    printf("input char: %s\r\n",cmd);
    printf("*: %s\r\n",strchr(cmd,'*'));
    printf(": : %s\r\n",strchr(cmd,':'));
    printf("?: %s\r\n",strchr(cmd,'?'));

    if(strchr(cmd, '*') != NULL){
        return;
        //basic cmd processing
    }else if((res=strchr(cmd,':')) != NULL){
        tkn = strtok(cmd,":");
        for(int i=0;i<dev->num_nodes;i++){
            if(strcmp(dev -> root[i] -> cmd.keyword , tkn) == 0){
                printf("cmd tree: %s chosen\r\n",dev->root[i]->cmd.keyword);
                process_tree(dev->root[i],++res);
                break;
            }
        }
        return;
    }else if(strchr(cmd,'?') != NULL){
        tkn = strtok(cmd,  "?");
        printf("token: %s\r\n",tkn);
        for(int i=0;i<dev->num_nodes;i++){
            if(strcmp(dev -> root[i] -> cmd.keyword , tkn) == 0){
                printf("cmd tree: %s chosen\r\n",dev->root[i]->cmd.keyword);
                dev -> root[i] ->cmd.callback(tkn);
                break;
            }
        }
        return;
    }else{
        printf("ROOT_PROCESSING FAILED\r\n");
    }
}
/*
scpi_res_t parse_tree(scpi_cmd_tree tr,char *cmd){
    char *tkn = strtok(cmd,":");

}

scpi_res_t get_node(scpi_cmd_node nd,char *cmd){

}*/