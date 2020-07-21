#include "test_graph.h"




void test_graph()
{
    int a0[] = {0,1,1,1,1,0,0,1,1,1,1};
    int a1[] = {0,0,1,0,0,0,0,0,0,0,0};
    int a2[] = {0,0,0,1,0,0,0,0,0,0,0};
    int a3[] = {0,0,0,0,1,0,0,0,0,0,0};
    int a4[] = {0,0,0,0,0,1,0,0,0,0,0};
    int a5[] = {0,0,0,0,0,0,1,0,0,0,0};
    int a6[] = {0,0,0,0,0,0,0,0,0,0,0};
    int a7[] = {0,0,0,0,0,1,0,0,0,0,0};
    int a8[] = {0,0,0,0,0,0,0,1,0,0,0};
    int a9[] = {0,0,0,0,0,0,0,0,1,0,0};
    int a10[] = {0,0,0,0,0,0,0,0,0,1,0};
    
    struct graph g = graph_init(11);
    g.matrix[0] = a0;
    g.matrix[1] = a1;
    g.matrix[2] = a2;
    g.matrix[3] = a3;
    g.matrix[4] = a4;
    g.matrix[5] = a5;
    g.matrix[6] = a6;
    g.matrix[7] = a7;
    g.matrix[8] = a8;
    g.matrix[9] = a9;
    g.matrix[10] = a10;
    
    //graph_bfs(&g);
    //graph_dfs(&g);
    graph_pfs(&g,dfs_pu);
    //write_group_to_dotfile(&g,"w+","");
    printf("\n");
}

