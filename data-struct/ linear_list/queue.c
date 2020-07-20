#include "queue.h"

struct queue queue_init()
{
    struct queue queue;
    queue.size = 0;
    queue.header = malloc(sizeof(struct queue_node));
    queue.trailer = malloc(sizeof(struct queue_node));
    queue.trailer->pred = queue.header;
    queue.header->succ = queue.trailer;
    return queue;
}

void queue_enqueue(struct queue *q, int e)
{
    struct queue_node *p = q->trailer;
    
    struct queue_node *new = malloc(sizeof(struct queue_node));
    struct queue_node *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    q->size++;
}

int queue_dequeue(struct queue *q)
{
    int tmp = q->header->succ->data;
    q->header->succ->succ->pred = q->header;
    q->header->succ = q->header->succ->succ;
    q->size--;
    return tmp;
}
