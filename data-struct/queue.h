#ifndef queue_h
#define queue_h


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


Queue initQueue(void);
void enqueue(Queue *Q, int e);

int dequeue(Queue *Q);

#endif /* queue_h */
