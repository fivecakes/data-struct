#include "binTree.h"
#include "queue.h"

static BinTreeQueue binTreeInitQueue()
{
    BinTreeQueue L;
    L.size = 0;
    L.header = malloc(sizeof(BinTreeQueueNode));
    L.trailer = malloc(sizeof(BinTreeQueueNode));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

static void binTreeEnqueue(BinTreeQueue *Q, BinNode *e)
{
    BinTreeQueueNode *p = Q->trailer;

    BinTreeQueueNode *new = malloc(sizeof(BinTreeQueueNode));
    BinTreeQueueNode *h = p->pred;

    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    Q->size++;
}

static BinNode *binTreeDequeue(BinTreeQueue *Q)
{
    BinNode *tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}

BinTree initBinTree(int e)
{
    BinTree T;
    T.root = malloc(sizeof(BinNode));
    T.root->lChild = NULL;
    T.root->rChild = NULL;
    T.root->data = e;
    return T;
}

static int updateHeight(BinNode *x)
{
    return x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
}

static void updateHeightAbove(BinNode *x)
{
    while (x != NULL) {
        updateHeight(x);
        x = x->parent;
    }
}

static BinNode *insertAsRC(BinNode *x, int e)
{
    x->rChild = malloc(sizeof(BinNode));
    x->rChild->parent = x;
    x->rChild->parent->lChild = NULL;
    x->rChild->parent->rChild = NULL;
    updateHeightAbove(x);
    return x->rChild;
}



//层次遍历
void travLevel(BinTree T)
{
    BinTreeQueue Q = binTreeInitQueue();
    binTreeEnqueue(&Q, T.root);
    
    while (Q.size) {
        BinNode *x = binTreeDequeue(&Q);
        if (x->lChild != NULL){
            printf("%s\n","lChild enquque");
            binTreeEnqueue(&Q, x->lChild);
        }
        
        if (x->rChild != NULL){
            printf("%s\n","rChild enquque");
            binTreeEnqueue(&Q, x->rChild);
        }
    }
}
