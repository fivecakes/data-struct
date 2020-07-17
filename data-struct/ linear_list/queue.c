#include "queue.h"

struct Queue queue_init()
{
    struct Queue L;
    L.size = 0;
    L.header = malloc(sizeof(struct QueueNode));
    L.trailer = malloc(sizeof(struct QueueNode));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

void queue_enqueue(struct Queue *Q, int e)
{
    struct QueueNode *p = Q->trailer;
    
    struct QueueNode *new = malloc(sizeof(struct QueueNode));
    struct QueueNode *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    Q->size++;
}

int queue_dequeue(struct Queue *Q)
{
    int tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}
