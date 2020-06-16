#ifndef queue_h
#define queue_h

#include "list.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef List Queue;

static Queue initQueue();
static void enqueue(Queue *Q, int e);

static int dequeue(Queue *Q);

#endif /* queue_h */
