#include "queue.h"

struct queue queue_init()
{
    struct queue L;
    L.size = 0;
    L.header = malloc(sizeof(struct queue_node));
    L.trailer = malloc(sizeof(struct queue_node));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

void queue_enqueue(struct queue *Q, int e)
{
    struct queue_node *p = Q->trailer;
    
    struct queue_node *new = malloc(sizeof(struct queue_node));
    struct queue_node *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    Q->size++;
}

int queue_dequeue(struct queue *Q)
{
    int tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}
