#ifndef queue_h
#define queue_h
#include "common.h"
struct QueueNode{
    int data;
    struct QueueNode *pred;
    struct QueueNode *succ;
};

struct Queue{
    int size;
    struct QueueNode *header;
    struct QueueNode *trailer;
};

typedef struct QueueNode QueueNode;
typedef struct Queue Queue;


Queue queue_init(void);
void queue_enqueue(Queue *Q, int e);

int queue_dequeue(Queue *Q);

#endif /* queue_h */
