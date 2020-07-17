#include "graph.h"


Graph graph_init(int (*arr)[5])
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
static int next_nbr(Graph *G,int i,int j)
{
    while (-1<j) {
        if (G->matrix[i][--j]) {
            break;
        }
    }
    return j;
}


static void bfs(Graph *G,int s)
{
    struct Queue Q = queue_init();
    G->graphNodes[s].status = DISCOVERED;
    queue_enqueue(&Q, s);
    
    while (Q.size) {
        int v = queue_dequeue(&Q);
        
        printf("%d",v);
        for (int u = next_nbr(G,v,4+1); -1<u; u=next_nbr(G,v,u)) {
            if (G->graphNodes[u].status == UNDISCOVERED) {
                G->graphNodes[u].status = DISCOVERED;
                queue_enqueue(&Q, u);
            }
        }
        
        G->graphNodes[v].status = VISITED;
    }
}

void graph_bfs(Graph *G)
{
    for (int i = 0; i<5; i++) {
        if (G->graphNodes[i].status == UNDISCOVERED) {
            bfs(G,i);
        }
    }
}

static void dfs(Graph *G,int s)
{
    G->graphNodes[s].status = DISCOVERED;

    printf("%d",s);
    for (int u = next_nbr(G,s,4+1); -1<u; u=next_nbr(G,s,u)) {
        if (G->graphNodes[u].status == UNDISCOVERED) {
            dfs(G,u);
        }
    }
    
    G->graphNodes[s].status = VISITED;

}

void graph_dfs(Graph *G)
{
    for (int i = 0; i<5; i++) {
        if (G->graphNodes[i].status == UNDISCOVERED) {
            dfs(G,i);
        }
    }
}

