#include "queue.h"

static Queue initQueue()
{
    return initList();
}

static void enqueue(Queue *Q, int e)
{
    ListNode *p = Q->trailer;
    insertBefore(p,e);
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
