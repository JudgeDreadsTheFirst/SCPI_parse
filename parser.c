
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_tokens(char *str){
    printf("Parse started\r\n");
    char *tok = strtok(str,":");

    while(tok){
        printf("token: %s\r\n",tok);
        tok = strtok(NULL,":");

    }

}
scpi_res_t debug_callback(char *keyword){
    printf("callback called for %s keyword\r\n",keyword);
    return RES_OK;
}

scpi_res_t debug_query_callback(char *keyword){
    printf("callback called for %s keyword, also is query\r\n",keyword);
    return RES_OK;
}

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

void process_tree(scpi_cmd_node *root,char *cmd){
    char *tkn;
    if(strchr(cmd,':') != NULL){
        tkn = strtok(cmd,":");
        printf("Got %s token from %s string.\r\n",tkn,cmd);
        for(int i =0;i < root->num_child;i++){
            if(strcmp(root->childs[i]->cmd.keyword,tkn) == 0){
                process_tree(root->childs[i],cmd);
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

void choose_root(scpi_dev *dev,char *cmd){
    printf("started %s func\r\n",__func__);
    char *tkn;
    const char *qu = "?";

    //const char *res;
    printf("input char: %s\r\n",cmd);
    printf("*: %s\r\n",strchr(cmd,'*'));
    printf(": : %s\r\n",strchr(cmd,':'));
    printf("?: %s\r\n",strchr(cmd,'?'));

    if(strchr(cmd, '*') != NULL){
        return;
        //basic cmd processing
    }else if(strchr(cmd,':') != NULL){
        tkn = strtok(cmd,":");
        for(int i=0;i<dev->num_nodes;i++){
            if(strcmp(dev -> root[i] -> cmd.keyword , tkn) == 0){
                printf("cmd tree: %s chosen\r\n",dev->root[i]->cmd.keyword);
                process_tree(dev->root[i],cmd);
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