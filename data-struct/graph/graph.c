#include "graph.h"


struct graph graph_init(int n)
{
    struct graph g;
    g.n = n;
    g.matrix = malloc(n*sizeof(int *));
    g.graph_nodes = malloc(n*sizeof(struct graph_node));
    
    for (int i = 0; i<g.n; i++) {
        g.graph_nodes[i].data = i;
        g.graph_nodes[i].status = UNDISCOVERED;
    }
    
    return g;
}

//找节点i的编号为j的邻居的下一个邻居
static int next_nbr(struct graph *g,int i,int j)
{
    while (-1<j) {
        if (g->matrix[i][--j]) {
            break;
        }
    }
    return j;
}


static void bfs(struct graph *g,int s)
{
    struct queue q = queue_init();
    g->graph_nodes[s].status = DISCOVERED;
    queue_enqueue(&q, s);
    
    while (q.size) {
        int v = queue_dequeue(&q);
        
        printf("%d",v);
        for (int u = next_nbr(g,v,g->n); -1<u; u=next_nbr(g,v,u)) {
            if (g->graph_nodes[u].status == UNDISCOVERED) {
                g->graph_nodes[u].status = DISCOVERED;
                queue_enqueue(&q, u);
            }
        }
        
        g->graph_nodes[v].status = VISITED;
    }
}

void graph_bfs(struct graph *g)
{
    for (int i = 0; i<g->n; i++) {
        if (g->graph_nodes[i].status == UNDISCOVERED) {
            bfs(g,i);
        }
    }
}

static void dfs(struct graph *g,int s)
{
    g->graph_nodes[s].status = DISCOVERED;

    printf("%d",s);
    for (int u = next_nbr(g,s,g->n); -1<u; u=next_nbr(g,s,u)) {
        if (g->graph_nodes[u].status == UNDISCOVERED) {
            dfs(g,u);
        }
    }
    
    g->graph_nodes[s].status = VISITED;

}

void graph_dfs(struct graph *g)
{
    for (int i = 0; i<g->n; i++) {
        if (g->graph_nodes[i].status == UNDISCOVERED) {
            dfs(g,i);
        }
    }
}

