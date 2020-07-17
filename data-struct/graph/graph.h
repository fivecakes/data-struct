#ifndef graph_h
#define graph_h
#include "common.h"
#include "queue.h"

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

struct graphNode{
    int data;
    int inDegree;
    int outDegree;
    
    int status;
    int dTime,fTime;
    int parent;
    int priority;
};


struct Graph{
    int (*matrix)[5];
    struct graphNode *graphNodes;
};


struct Graph graph_init(int (*arr)[5]);
void graph_bfs(struct Graph *G);
void graph_dfs(struct Graph *G);

#endif /* graph_h */
