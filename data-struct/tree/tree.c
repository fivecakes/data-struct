#include "tree.h"

static struct tree_queue tree_init_queue()
{
    struct tree_queue L;
    L.size = 0;
    L.header = malloc(sizeof(struct tree_queue_node));
    L.trailer = malloc(sizeof(struct tree_queue_node));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

static void tree_enqueue(struct tree_queue *Q, struct tree_node *e)
{
    struct tree_queue_node *p = Q->trailer;

    struct tree_queue_node *new = malloc(sizeof(struct tree_queue_node));
    struct tree_queue_node *h = p->pred;

    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    Q->size++;
}

static struct tree_node *tree_dequeue(struct tree_queue *Q)
{
    if (Q->size == 0) {
        return NULL;
    }
    struct tree_node *tmp = Q->header->succ->data;
    Q->header->succ->succ->pred = Q->header;
    Q->header->succ = Q->header->succ->succ;
    Q->size--;
    return tmp;
}


static struct tree_stack tree_init_stack()
{
    struct tree_stack S;
    S.elem = malloc(2* sizeof(int*));
    S.capacity =2;
    S.size = 0;
    return S;
}

//扩容
static void expand(struct tree_stack *S)
{
    if(S->size < S->capacity) return; //尚未满员，不必扩容
    S->elem = realloc(S->elem,(S->capacity<<=1)*sizeof(int));
}

static void tree_push(struct tree_stack *S, struct tree_node *e)
{
    expand(S);
    *(S->elem+S->size) = e;
    S->size++;
}

static struct tree_node *tree_pop(struct tree_stack *S)
{
    S->size--;
    return *(S->elem + S->size);
}



struct tree init_tree()
{
    struct tree T;
    T.top = NULL;
    T.size = 0;
    T.hot = NULL;
    
    return T;
}



//层次遍历
void level_traversal(struct tree T,void visit(struct tree_node *e))
{
    struct tree_queue Q = tree_init_queue();
    tree_enqueue(&Q, T.top->left_child);
    
    while (Q.size) {
        struct tree_node *x = tree_dequeue(&Q);
        
        visit(x);
        
        if (x->left_child != NULL){
            tree_enqueue(&Q, x->left_child);
        }
        
        if (x->right_child != NULL){
            tree_enqueue(&Q, x->right_child);
        }
    }
}

void visit_along_left_branch(struct tree_node *x,void visit(struct tree_node *e),struct tree_stack *S)
{
    while (x!= NULL) {
        visit(x);
        tree_push(S,x->right_child);
        x = x->left_child;
    }
}

//先序遍历
void pre_traversal(struct tree T,void visit(struct tree_node *e))
{
    struct tree_stack S = tree_init_stack();
    struct tree_node *x = T.top->left_child;
    while (1) {
        visit_along_left_branch(x,visit,&S);
        if (S.size==0) {
            break;
        }else{
            x = tree_pop(&S);
        }
    }
}

void go_alone_left_branch(struct tree_node *x,struct tree_stack *S)
{
    while (x != NULL) {
        tree_push(S,x);
        x = x->left_child;
    }
}

//中序遍历
void in_traversal(struct tree T,void visit(struct tree_node *e))
{
    struct tree_stack S = tree_init_stack();
    struct tree_node *x = T.top->left_child;
    while (1) {
        go_alone_left_branch(x,&S);
        if (S.size==0) {
            break;
        }else{
            x = tree_pop(&S);
            visit(x);
            x = x->right_child;
        }
    }
}

void visit(struct tree_node *e)
{
    printf("%d,",e->data);
}


static void print_dot_node(FILE* fp ,struct tree_node *e)
{
    if (!e) return;
    if (e->color == RED) {
        fprintf(fp, " node%p [label=\"%d (h%d)\",color=red,fontcolor=white]\n",e,e->data,e->height);
    }else if (e->color == BLACK){
        fprintf(fp, " node%p [label=\"%d (h%d)\",color=black,fontcolor=white]\n",e,e->data,e->height);
    }else{
       fprintf(fp, " node%p[label=\"%d (h%d)\"]\n", e,e->data,e->height);
    }
    
    
    if (!e->left_child && !e->right_child) {
        return;
    }
    
    if (e->left_child) {
        fprintf(fp, " node%p -> node%p\n", e ,e->left_child) ;
        fprintf(fp, " node%p -> node%p\n",  e->left_child,e->left_child->parent) ;
        print_dot_node(fp ,e->left_child);
    }else{
        fprintf(fp, " lChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> lChild%p[style = dotted]\n", e,e);
    }
    
    if (e->right_child) {
        fprintf(fp, " node%p -> node%p\n", e ,e->right_child) ;
        fprintf(fp, " node%p -> node%p\n",  e->right_child,e->right_child->parent) ;
        print_dot_node(fp ,e->right_child);
    }else{
        fprintf(fp, " rChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> rChild%p[style = dotted]\n", e,e);
    }
}



void write_tree_to_dotfile(struct tree *T,char opt[],char info[])
{
    FILE* fp = fopen(DOT_FILE_PATH, opt);
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
    print_dot_node(fp ,T->top);
    fprintf(fp, "}\n");
    fclose(fp);
}
