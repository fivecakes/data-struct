#include "binTree.h"

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

static void binTreeEnqueue(BinTreeQueue *Q, TreeNode *e)
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

static TreeNode *binTreeDequeue(BinTreeQueue *Q)
{
    if (Q->size == 0) {
        return NULL;
    }
    TreeNode *tmp = Q->header->succ->data;
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

static void binTreePush(BinTreeStack *S, TreeNode *e)
{
    expand(S);
    *(S->elem+S->size) = e;
    S->size++;
}

static TreeNode *binTreePop(BinTreeStack *S)
{
    S->size--;
    return *(S->elem + S->size);
}

BinTree initBinTree()
{
    BinTree T;
    T.top = malloc(sizeof(TreeNode));
    T.top->parent = NULL;
    T.top->lChild = NULL;
    T.top->rChild = NULL;
    T.top->data = INT_MAX;
    T.top->height = 0;
    
    return T;
}

int updateHeight(TreeNode *x)
{
    x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
    //printf("updateheight %d,height=%d\n",x->data,x->height);
    return x->height;
}

void updateHeightAbove(TreeNode *x)
{
    //printf("updateHeightAbove %d\n",x->data);
    while (x != NULL) {
        updateHeight(x);
        x = x->parent;
    }
}

TreeNode *insertAsRC(TreeNode *x, int e)
{
    TreeNode *new = malloc(sizeof(TreeNode));
    new->parent = x;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->height = 0;
    
    x->rChild = new;
    
    updateHeightAbove(x);
    return new;
}

TreeNode *insertAsLC(TreeNode *x, int e)
{
    TreeNode *new = malloc(sizeof(TreeNode));
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
void travLevel(BinTree T,void visit(TreeNode *e))
{
    BinTreeQueue Q = binTreeInitQueue();
    binTreeEnqueue(&Q, T.top);
    
    while (Q.size) {
        TreeNode *x = binTreeDequeue(&Q);
        
        visit(x);
        
        if (x->lChild != NULL){
            binTreeEnqueue(&Q, x->lChild);
        }
        
        if (x->rChild != NULL){
            binTreeEnqueue(&Q, x->rChild);
        }
    }
}

void visitAlongLeftBranch(TreeNode *x,void visit(TreeNode *e),BinTreeStack *S)
{
    while (x!= NULL) {
        visit(x);
        binTreePush(S,x->rChild);
        x = x->lChild;
    }
}

//先序遍历
void travPre(BinTree T,void visit(TreeNode *e))
{
    BinTreeStack S = binTreeInitStack();
    TreeNode *x = T.top;
    while (1) {
        visitAlongLeftBranch(x,visit,&S);
        if (S.size==0) {
            break;
        }else{
            x = binTreePop(&S);
        }
    }
}

void goAloneLeftBranch(TreeNode *x,BinTreeStack *S)
{
    while (x != NULL) {
        binTreePush(S,x);
        x = x->lChild;
    }
}

//中序遍历
void travIn(BinTree T,void visit(TreeNode *e))
{
    BinTreeStack S = binTreeInitStack();
    TreeNode *x = T.top;
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

void visit(TreeNode *e)
{
    printf("%d,",e->data);
}


static void printDotNode(FILE* fp ,TreeNode *e)
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



void writeTreeToDotFile(BinTree T,char opt[],char info[])
{
    FILE* fp = fopen("/Users/book/Codes/data-struct/data-struct/tree.dot", opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//%s",info);
    fprintf(fp, "\ndigraph {\n");
    fprintf(fp, " n%dh%d\n [label=\"top\"][style = dotted]\n", T.top->data,T.top->height);

    if (T.top->lChild) {
        fprintf(fp, " n%dh%d -> n%dh%d\n", T.top->data,T.top->height, T.top->lChild->data,T.top->lChild->height) ;
        fprintf(fp, " n%dh%d -> n%dh%d\n",  T.top->lChild->data,T.top->lChild->height,T.top->lChild->parent->data,T.top->lChild->parent->height) ;

        printDotNode(fp ,T.top->lChild);
    }
    fprintf(fp, "}\n");
    fclose(fp);
}
