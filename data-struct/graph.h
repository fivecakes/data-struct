//
//  graph.h
//  data-struct
//
//  Created by book on 2020/6/18.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>
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

typedef struct graphNode graphNode;

struct Graph{
    int (*matrix)[5];
    graphNode *graphNodes;
};

typedef struct Graph Graph;

Graph initGraph(int (*arr)[5]);
static void BFS(Graph *G,int s);
void bfs(Graph *G);
static void DFS(Graph *G,int s);
void dfs(Graph *G);

#endif /* graph_h */
