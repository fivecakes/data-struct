#include "graph.h"

/**
 图可以通过遍历转化成一棵树
 */

struct graph graph_init(int n)
{
    struct graph g;
    g.n = n;
    g.matrix = malloc(n*sizeof(int *));
    g.graph_nodes = malloc(n*sizeof(struct graph_node));
    
    for (int i = 0; i<g.n; i++) {
        g.graph_nodes[i].data = i;
        g.graph_nodes[i].status = UNDISCOVERED;
        g.graph_nodes[i].priority = 0;
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


void dfs_pu(struct graph * g, struct heap *pq,int uk, int v )
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        if(g->graph_nodes[v].priority<g->graph_nodes[uk].priority+1){
            g->graph_nodes[v].priority=g->graph_nodes[uk].priority+1;
            struct heap_node hn;
            hn.data = v;
            hn.priority =g->graph_nodes[uk].priority+1;
            heap_insert(pq, hn);
        }
    }
}

void bfs_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        if(g->graph_nodes[v].priority<g->graph_nodes[uk].priority-1){
            g->graph_nodes[v].priority=g->graph_nodes[uk].priority-1;
            struct heap_node hn;
            hn.data = v;
            hn.priority =g->graph_nodes[uk].priority+1;
            heap_insert(pq, hn);
        }
    }
}

void prim_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        if(g->graph_nodes[v].priority<g->matrix[uk][v]){
            g->graph_nodes[v].priority=g->matrix[uk][v];
            struct heap_node hn;
            hn.data = v;
            hn.priority =g->matrix[uk][v];
            heap_insert(pq, hn);
        }
    }
}

void dijkstra_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        int w = g->matrix[uk][v]+g->graph_nodes[uk].priority;
        if(g->graph_nodes[v].priority<w){
            g->graph_nodes[v].priority=w;
            struct heap_node hn;
            hn.data = v;
            hn.priority =w;
            heap_insert(pq, hn);
        }
    }
}

static void pfs(struct graph *g,int s, void prio_updater(struct graph *g,struct heap *pq,int uk,int i))
{
    //起点s加入PFS树
    g->graph_nodes[s].status = VISITED;
    g->graph_nodes[s].priority = 10;
    printf("%d(%d),",s,g->graph_nodes[s].priority);
    struct heap pq = heap_vector_init();
    
    while (1) {
        //对s的所有邻居，更新优先级
        for (int u = next_nbr(g,s,g->n); -1<u; u=next_nbr(g,s,u))
            prio_updater(g,&pq,s,u);

        //选择优先级最高的顶点s
        s = heap_del_max(&pq).data;
        
        //如果所有节点都遍历过了，退出否则，将s加入遍历树
        if (g->graph_nodes[s].status == VISITED){
            break;
        }else{
            g->graph_nodes[s].status = VISITED;
            printf("%d(%d),",s,g->graph_nodes[s].priority);
        }
    }
}

void graph_pfs(struct graph *g, void prio_updater(struct graph *g,struct heap *pq,int uk,int i))
{
    for (int i = 0; i<g->n; i++) {
        if (g->graph_nodes[i].status == UNDISCOVERED) {
            pfs(g,i,prio_updater);
        }
    }
}



void write_group_to_dotfile(struct graph *g,char opt[],char info[])
{
    FILE* fp = fopen(DOT_FILE_PATH, opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//%s",info);
    fprintf(fp, "\ndigraph {\n");
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [style=filled,color=lightblue;];\n\n");
    for (int i=0; i<g->n; i++) {
        for (int j=0; j<g->n; j++) {
            fprintf(fp, " node%d[label=\"%d\"]\n", i,i);
            if (g->matrix[i][j]) {
                fprintf(fp, " node%d -> node%d\n", i,j) ;
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
}
