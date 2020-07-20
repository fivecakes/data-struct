#ifndef graph_h
#define graph_h
#include "common.h"
#include "queue.h"

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
    int (*matrix)[5];
    struct graph_node *graph_nodes;
};


struct graph graph_init(int (*arr)[5]);
void graph_bfs(struct graph *g);
void graph_dfs(struct graph *g);

#endif /* graph_h */
