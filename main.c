#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    printf("START!\r\n");
    scpi_dev *par = malloc(sizeof(scpi_dev));
    par->num_nodes =3;
    par->interface = NULL;

    printf("root init!\r\n");
    scpi_cmd_node *root1;
    scpi_cmd_node *root2;
    scpi_cmd_node *root3;
    scpi_cmd_node *child2,*child3;

    printf("cmd init!\r\n");
    scpi_cmd_t cmd_lst[] = {
            {.keyword = "SYSTEM", .callback = debug_callback},
            {.keyword = "POW",.callback = debug_callback},
            {.keyword = "FREQ", .callback = debug_callback},
            {.keyword = "LEV", .callback = debug_callback},
            {.keyword = "CONT", .callback = debug_callback},
            {NULL,NULL}
    };
    printf("node init!\r\n");
    root1 = init_node(cmd_lst[0],0);
    root2 = init_node(cmd_lst[1],1);
    root3 = init_node(cmd_lst[2],1);
    child2 = init_node(cmd_lst[3],0);
    child3 = init_node(cmd_lst[4],0);
    printf("tree init!\r\n");
    par->root[0] = root1;
    par->root[1] = root2;
    par->root[2] = root3;
    par->root[3] = NULL;
    par->root[4] = NULL;
    root2->childs[0] = child2;
    root3->childs[0] = child3;


    printf("str init!\r\n");
    char str[] = "POW:LEV";
    char str2[] = "FREQ:CONT:SET";
    printf("str: %s\r\n",str);
    printf("TESTING CALLBACKS FOR ROOT\r\n");
    choose_root(par,str);

    print_tokens(str2);

    free(par);
    free(root1);
    free(root2);
    free(root3);
    free(child2);
    free(child3);
    return 0;
}