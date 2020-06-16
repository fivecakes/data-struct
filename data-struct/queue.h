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


static Queue initQueue(void);
static void enqueue(Queue *Q, int e);

static int dequeue(Queue *Q);

#endif /* queue_h */
