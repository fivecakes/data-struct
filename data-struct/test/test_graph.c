//
//  testGraph.c
//  data-struct
//
//  Created by book on 2020/6/23.
//  Copyright © 2020 book. All rights reserved.
//

#include "test_graph.h"




void testGraph()
{
    int arr[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,1},
        {0,1,1,0,0},
        {0,1,0,1,0}
    };
    Graph G = graph_init(arr);
    graph_dfs(&G);
    printf("\n");
}
