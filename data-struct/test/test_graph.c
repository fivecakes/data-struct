#include "test_graph.h"




void test_graph()
{
    int a0[]  = {0,3,0,5,0,0,0,0,0,0,0,0,0};
    int a1[]  = {3,0,0,0,11,0,0,0,0,0,0,0,0};
    int a2[]  = {0,0,0,7,0,2,0,0,0,0,0,0,0};
    int a3[]  = {5,0,7,0,0,8,0,0,0,0,0,0,0};
    int a4[]  = {0,11,0,0,0,0,0,4,3,0,0,0,0};
    int a5[]  = {0,0,2,8,0,0,1,6,0,0,0,0,0};
    int a6[]  = {0,0,0,0,0,1,0,0,0,4,0,0,0};
    int a7[]  = {0,0,0,0,4,6,0,0,2,4,0,0,0};
    int a8[]  = {0,0,0,0,3,0,0,2,0,0,0,13,0};
    int a9[]  = {0,0,0,0,0,0,4,4,0,0,7,0,0};
    int a10[] = {0,0,0,0,0,0,0,0,0,7,0,2,1};
    int a11[] = {0,0,0,0,0,0,0,0,13,0,2,0,5};
    int a12[] = {0,0,0,0,0,0,0,0,0,0,1,5,0};
    
    struct graph g = graph_init(13);
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
    g.matrix[11] = a11;
    g.matrix[12] = a12;
    
    graph_pfs(&g,dijkstra_pu);
    //write_group_to_dotfile(&g,"w+","");
    printf("\n");
}

