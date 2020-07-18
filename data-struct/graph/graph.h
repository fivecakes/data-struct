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
    int dTime,fTime;
    int parent;
    int priority;
};


struct graph{
    int (*matrix)[5];
    struct graph_node *graphNodes;
};


struct graph graph_init(int (*arr)[5]);
void graph_bfs(struct graph *G);
void graph_dfs(struct graph *G);

#endif /* graph_h */
