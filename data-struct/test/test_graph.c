#include "test_graph.h"




void test_graph()
{
    int arr[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,1},
        {0,1,1,0,0},
        {0,1,0,1,0}
    };
    struct graph g = graph_init(arr);
    graph_dfs(&g);
    printf("\n");
}
