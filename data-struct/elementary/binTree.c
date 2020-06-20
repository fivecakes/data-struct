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
    if (Q->size == 0) {
        return NULL;
    }
    BinNode *tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}


static BinTreeStack binTreeInitStack()
{
    BinTreeStack S;
    S.elem = malloc(2* sizeof(int*));
    S.capacity =2;
    S.size = 0;
    return S;
}

//扩容
static void expand(BinTreeStack *S)
{
    if(S->size < S->capacity) return; //尚未满员，不必扩容
    S->elem = realloc(S->elem,(S->capacity<<=1)*sizeof(int));
}

static void binTreePush(BinTreeStack *S, BinNode *e)
{
    expand(S);
    *(S->elem+S->size) = e;
    S->size++;
}

static BinNode *binTreePop(BinTreeStack *S)
{
    S->size--;
    return *(S->elem + S->size);
}

BinTree initBinTree(int e)
{
    BinTree T;
    T.root = malloc(sizeof(BinNode));
    T.root->lChild = NULL;
    T.root->rChild = NULL;
    T.root->data = e;
    T.root->height = 0;
    
    return T;
}

static int updateHeight(BinNode *x)
{
    return x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
}

void updateHeightAbove(BinNode *x)
{
    while (x != NULL) {
        updateHeight(x);
        x = x->parent;
    }
}

BinNode *insertAsRC(BinNode *x, int e)
{
    BinNode *new = malloc(sizeof(BinNode));
    new->parent = x;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->height = 0;
    
    x->rChild = new;
    
    updateHeightAbove(x);
    return new;
}

BinNode *insertAsLC(BinNode *x, int e)
{
    BinNode *new = malloc(sizeof(BinNode));
    new->parent = x;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->height = 0;
    
    x->lChild = new;
    
    updateHeightAbove(x);
    return new;
}



//层次遍历
void travLevel(BinTree T,void visit(BinNode *e))
{
    BinTreeQueue Q = binTreeInitQueue();
    binTreeEnqueue(&Q, T.root);
    
    while (Q.size) {
        BinNode *x = binTreeDequeue(&Q);
        
        visit(x);
        
        if (x->lChild != NULL){
            binTreeEnqueue(&Q, x->lChild);
        }
        
        if (x->rChild != NULL){
            binTreeEnqueue(&Q, x->rChild);
        }
    }
}

void visitAlongLeftBranch(BinNode *x,void visit(BinNode *e),BinTreeStack *S)
{
    while (x!= NULL) {
        visit(x);
        binTreePush(S,x->rChild);
        x = x->lChild;
    }
}

//先序遍历
void travPre(BinTree T,void visit(BinNode *e))
{
    BinTreeStack S = binTreeInitStack();
    BinNode *x = T.root;
    while (1) {
        visitAlongLeftBranch(x,visit,&S);
        if (S.size==0) {
            break;
        }else{
            x = binTreePop(&S);
        }
    }
}

void goAloneLeftBranch(BinNode *x,BinTreeStack *S)
{
    while (x != NULL) {
        binTreePush(S,x);
        x = x->lChild;
    }
}

//中序遍历
void travIn(BinTree T,void visit(BinNode *e))
{
    BinTreeStack S = binTreeInitStack();
    BinNode *x = T.root;
    while (1) {
        goAloneLeftBranch(x,&S);
        if (S.size==0) {
            break;
        }else{
            x = binTreePop(&S);
            visit(x);
            x = x->rChild;
        }
    }
}


//图形化输出二叉树
void printTG(BinTree T)
{
    BinTreeQueue Q = binTreeInitQueue();
    binTreeEnqueue(&Q, T.root);
    printf("height=%d\n",T.root->height);
    int i, j, depth = T.root->height+1;
    char str[3] = "   ";
    
    for (j = 0; j < depth; j++) {
        int w = 1 << (depth - j);
        for (i = 0; i < 1 << j; i++)
        {
            BinNode *x = binTreeDequeue(&Q);
            if (x) {
                sprintf(str, "%d", x->data);
            }else{
                str[0] = ' ';
                str[1] = ' ';
                str[2] = ' ';
            }
            
            printf("%*s%*c", w, str, w, ' ');
            
            if (!x) {
                binTreeEnqueue(&Q, NULL);
                binTreeEnqueue(&Q, NULL);
            }else{
                binTreeEnqueue(&Q, x->lChild);
                binTreeEnqueue(&Q, x->rChild);
            }
        }
        printf("\n");
    }

    printf("\n");
}
