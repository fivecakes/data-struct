#ifndef queue_h
#define queue_h
#include "common.h"
struct queue_node{
    int data;
    struct queue_node *pred;
    struct queue_node *succ;
};

struct queue{
    int size;
    struct queue_node *header;
    struct queue_node *trailer;
};



struct queue queue_init(void);
void queue_enqueue(struct queue *q, int e);

int queue_dequeue(struct queue *q);

#endif /* queue_h */
