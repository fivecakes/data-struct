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
    T.header = malloc(sizeof(BinNode));
    
    T.root->parent = T.header;
    T.root->lChild = NULL;
    T.root->rChild = NULL;
    T.root->data = e;
    T.root->height = 0;
    
    T.header->parent = NULL;
    T.header->lChild = T.root;
    T.header->rChild = NULL;
    T.header->data = INT_MAX;
    T.header->height = 0;
    
    return T;
}

int updateHeight(BinNode *x)
{
    x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
    //printf("updateheight %d,height=%d\n",x->data,x->height);
    return x->height;
}

void updateHeightAbove(BinNode *x)
{
    //printf("updateHeightAbove %d\n",x->data);
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

void visit(BinNode *e)
{
    printf("%d,",e->data,e->height);
}

void printDotNode(FILE* fp ,BinNode *e)
{
    if (!e->lChild && !e->rChild) {
        return;
    }
    if (e->lChild) {
        fprintf(fp, " n%dh%d -> n%dh%d\n", e->data,e->height, e->lChild->data,e->lChild->height) ;
        fprintf(fp, " n%dh%d -> n%dh%d\n",  e->lChild->data,e->lChild->height,e->lChild->parent->data,e->lChild->parent->height) ;
        printDotNode(fp ,e->lChild);
    }else{
        fprintf(fp, " lChild%d [label=\"Null\"][style = dotted]\n", e->data);
        fprintf(fp, " n%dh%d -> lChild%d[style = dotted]\n", e->data,  e->height,e->data);
    }
    
    if (e->rChild) {
        fprintf(fp, " n%dh%d -> n%dh%d\n", e->data,e->height, e->rChild->data,e->rChild->height) ;
        fprintf(fp, " n%dh%d -> n%dh%d\n",  e->rChild->data,e->rChild->height,e->rChild->parent->data,e->rChild->parent->height) ;
        printDotNode(fp ,e->rChild);
    }else{
        fprintf(fp, " rChild%d [label=\"Null\"][style = dotted]\n", e->data);
        fprintf(fp, " n%dh%d -> rChild%d[style = dotted]\n", e->data, e->height,e->data);
    }
}

void writeToDot(BinTree T,char opt[],char info[]){
    //以追写的方式打开文件
    FILE* fp = fopen("/Users/book/Codes/data-struct/data-struct/tree.dot", opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//");
    fprintf(fp, info);
    fprintf(fp, "\ndigraph {\n");
    fprintf(fp, " n%dh%d\n", T.root->data,T.root->height) ;
    printDotNode(fp ,T.root);
    fprintf(fp, "}\n"); // 设置null节点的属性
    fclose(fp);
}
