#include "test_graph.h"




void test_graph()
{
    int a0[] = {0,0,1,0,0};
    int a1[] = {0,0,1,0,0};
    int a2[] = {0,0,0,0,1};
    int a3[] = {0,1,1,0,0};
    int a4[] = {0,1,0,1,0};
    
    struct graph g = graph_init(5);
    g.matrix[0] = a0;
    g.matrix[1] = a1;
    g.matrix[2] = a2;
    g.matrix[3] = a3;
    g.matrix[4] = a4;
    
    //graph_bfs(&g);
    graph_dfs(&g);
    printf("\n");
}
