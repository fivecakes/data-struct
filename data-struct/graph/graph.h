#ifndef graph_h
#define graph_h
#include "common.h"
#include "heap.h"

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

struct graph_node{
    int data;
    int in_degree;
    int out_degree;
    
    int status;
    int d_time,f_time;
    int parent;
    int priority;
};


struct graph{
    int **matrix;
    int n;
    struct graph_node *graph_nodes;
};


struct graph graph_init(int n);
void graph_pfs(struct graph *g, void prio_updater(struct graph *g,struct heap *pq,int uk,int i));
void dfs_pu(struct graph * g, struct heap *pq,int uk, int v );
void bfs_pu(struct graph * g, struct heap *pq,int uk, int v);
void write_group_to_dotfile(struct graph *g,char opt[],char info[]);
#endif
