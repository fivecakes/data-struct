#include "graph.h"

/**
 图可以通过遍历转化成一棵树，这棵树叫做生成树(或支撑树)
 深度优先遍历出来的树叫深度优先生成树
 广度优先遍历出来的树叫广度优先生成树
 各边权值之和最小的生成树叫最小生成树
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
        g.graph_nodes[i].parent = -1;
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

/**
 优先级越小越优先
 自节点优先级 = 父节点优先级 -1
 越深的节点优先级越小，越优先
 */
void dfs_pu(struct graph * g, struct heap *pq,int uk, int v )
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        g->graph_nodes[v].priority=g->graph_nodes[uk].priority-1;
        heap_insert(pq, v,g->graph_nodes[uk].priority-1);
        g->graph_nodes[v].parent = uk;
    }
}

/**
优先级越小越优先
自节点优先级 = 父节点优先级 + 1
越深的节点优先级越大，越不优先
*/
void bfs_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        g->graph_nodes[v].priority=g->graph_nodes[uk].priority+1;
        heap_insert(pq, v,g->graph_nodes[uk].priority+1);
        g->graph_nodes[v].parent = uk;
    }
}

/**
总是朝着权值最小的边扩展生成树
*/
void prim_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        g->graph_nodes[v].priority = g->matrix[uk][v];
        heap_insert(pq, v, g->matrix[uk][v]);
        g->graph_nodes[v].parent = uk;
    }
}

/**
贪心的优先探索累积权值最小的那条路径，这是贪心算法，结果并不一定是全局最优的
*/
void dijkstra_pu(struct graph * g, struct heap *pq,int uk, int v)
{
    if (g->graph_nodes[v].status == UNDISCOVERED){
        g->graph_nodes[v].priority = g->graph_nodes[uk].priority+g->matrix[uk][v];
        heap_insert(pq, v, g->graph_nodes[uk].priority+g->matrix[uk][v]);
        g->graph_nodes[v].parent = uk;
    }
}


static void pfs(struct graph *g,int s, void prio_updater(struct graph *g,struct heap *pq,int uk,int i))
{
    //起点s加入PFS树
    g->graph_nodes[s].status = VISITED;
    g->graph_nodes[s].priority = 100;
    printf("%d(%d),",s,g->graph_nodes[s].priority);
    struct heap pq = heap_vector_init();
    
    while (1) {
        //对s的所有邻居，更新优先级
        for (int u = next_nbr(g,s,g->n); -1<u; u=next_nbr(g,s,u))
            prio_updater(g,&pq,s,u);

        //选择优先级小的顶点s
        s = heap_del_min(&pq).data;
        
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
    fprintf(fp, " node [style=filled,color=lightblue;]\n");
    fprintf(fp, " rankdir=LR\n");
    for (int i=0; i<g->n; i++) {
        fprintf(fp, " node%d[label=\"%d\"]\n", i,i);
        for (int j=i; j<g->n; j++) {
            if (g->matrix[i][j]) {
                fprintf(fp, " node%d -> node%d[dir=\"none\",label=\"%d\"]\n", i,j,g->matrix[i][j]) ;
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
}
