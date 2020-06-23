//
//  graph.c
//  data-struct
//
//  Created by book on 2020/6/18.
//  Copyright © 2020 book. All rights reserved.
//

#include "graph.h"


Graph initGraph(int (*arr)[5])
{
    Graph G;
    G.matrix = arr;
    G.graphNodes = malloc(5*sizeof(graphNode));
    
    for (int i = 0; i<5; i++) {
        G.graphNodes[i].data = i;
        G.graphNodes[i].status = UNDISCOVERED;
    }
    
    return G;
}

//找节点i的编号为j的邻居的下一个邻居
int nextNbr(Graph *G,int i,int j)
{
    while (-1<j) {
        if (G->matrix[i][--j]) {
            break;
        }
    }
    return j;
}

void bfs(Graph *G)
{
    for (int i = 0; i<5; i++) {
        if (G->graphNodes[i].status == UNDISCOVERED) {
            BFS(G,i);
        }
    }
}

void BFS(Graph *G,int s)
{
    Queue Q = initQueue();
    G->graphNodes[s].status = DISCOVERED;
    enqueue(&Q, s);
    
    while (Q.size) {
        int v = dequeue(&Q);
        
        printf("%d",v);
        for (int u = nextNbr(G,v,4+1); -1<u; u=nextNbr(G,v,u)) {
            if (G->graphNodes[u].status == UNDISCOVERED) {
                G->graphNodes[u].status = DISCOVERED;
                enqueue(&Q, u);
            }
        }
        
        G->graphNodes[v].status = VISITED;
    }
}

void dfs(Graph *G)
{
    for (int i = 0; i<5; i++) {
        if (G->graphNodes[i].status == UNDISCOVERED) {
            DFS(G,i);
        }
    }
}

void DFS(Graph *G,int s)
{
    G->graphNodes[s].status = DISCOVERED;

    printf("%d",s);
    for (int u = nextNbr(G,s,4+1); -1<u; u=nextNbr(G,s,u)) {
        if (G->graphNodes[u].status == UNDISCOVERED) {
            DFS(G,u);
        }
    }
    
    G->graphNodes[s].status = VISITED;

}

