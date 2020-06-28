#include "Tree.h"

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

Tree initBinTree()
{
    Tree T;
    T.top = malloc(sizeof(TreeNode));
    T.top->parent = NULL;
    T.top->lChild = NULL;
    T.top->rChild = NULL;
    T.top->data = INT_MAX;
    T.top->color = WHITE;
    T.top->height = 0;
    
    return T;
}





//层次遍历
void travLevel(Tree T,void visit(TreeNode *e))
{
    BinTreeQueue Q = binTreeInitQueue();
    binTreeEnqueue(&Q, T.top->lChild);
    
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
void travPre(Tree T,void visit(TreeNode *e))
{
    BinTreeStack S = binTreeInitStack();
    TreeNode *x = T.top->lChild;
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
void travIn(Tree T,void visit(TreeNode *e))
{
    BinTreeStack S = binTreeInitStack();
    TreeNode *x = T.top->lChild;
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
    if (e->color == RED) {
        fprintf(fp, " node%p [label=\"%d (h%d)\",color=red,fontcolor=white]\n",e,e->data,e->height);
    }else if (e->color == BLACK){
        fprintf(fp, " node%p [label=\"%d (h%d)\",color=black,fontcolor=white]\n",e,e->data,e->height);
    }else{
       fprintf(fp, " node%p[label=\"%d (h%d)\"]\n", e,e->data,e->height);
    }
    
    
    if (!e->lChild && !e->rChild) {
        return;
    }
    
    if (e->lChild) {
        fprintf(fp, " node%p -> node%p\n", e ,e->lChild) ;
        fprintf(fp, " node%p -> node%p\n",  e->lChild,e->lChild->parent) ;
        printDotNode(fp ,e->lChild);
    }else{
        fprintf(fp, " lChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> lChild%p[style = dotted]\n", e,e);
    }
    
    if (e->rChild) {
        fprintf(fp, " node%p -> node%p\n", e ,e->rChild) ;
        fprintf(fp, " node%p -> node%p\n",  e->rChild,e->rChild->parent) ;
        printDotNode(fp ,e->rChild);
    }else{
        fprintf(fp, " rChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> rChild%p[style = dotted]\n", e,e);
    }
}



void writeTreeToDotFile(Tree T,char opt[],char info[])
{
    FILE* fp = fopen(dot_file_path, opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//%s",info);
    fprintf(fp, "\ndigraph {\n");
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [style=filled,color=lightblue;];\n\n");
    fprintf(fp, " node%p [label=\"top\"][style = dotted]\n", T.top);

    if (T.top->lChild) {
        fprintf(fp, " node%p -> node%p\n", T.top, T.top->lChild) ;
        fprintf(fp, " node%p -> node%p\n",  T.top->lChild,T.top) ;

        printDotNode(fp ,T.top->lChild);
    }
    fprintf(fp, "}\n");
    fclose(fp);
}
