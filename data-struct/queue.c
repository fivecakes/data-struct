#include "queue.h"

static Queue initQueue()
{
    Queue L;
    L.size = 0;
    L.header = malloc(sizeof(QueueNode));
    L.trailer = malloc(sizeof(QueueNode));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

static void insertBeforeQueueNode(QueueNode *p,int e)
{
    QueueNode *new = malloc(sizeof(QueueNode));
    QueueNode *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
}

static void enqueue(Queue *Q, int e)
{
    QueueNode *p = Q->trailer;
    insertBeforeQueueNode(p,e);
    Q->size++;
}

static int dequeue(Queue *Q)
{
    int tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}
