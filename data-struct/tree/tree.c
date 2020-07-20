#include "tree.h"

static struct tree_queue tree_init_queue()
{
    struct tree_queue queue;
    queue.size = 0;
    queue.header = malloc(sizeof(struct tree_queue_node));
    queue.trailer = malloc(sizeof(struct tree_queue_node));
    queue.trailer->pred = queue.header;
    queue.header->succ = queue.trailer;
    return queue;
}

static void tree_enqueue(struct tree_queue *q, struct tree_node *e)
{
    struct tree_queue_node *p = q->trailer;

    struct tree_queue_node *new = malloc(sizeof(struct tree_queue_node));
    struct tree_queue_node *h = p->pred;

    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    q->size++;
}

static struct tree_node *tree_dequeue(struct tree_queue *q)
{
    if (q->size == 0) {
        return NULL;
    }
    struct tree_node *tmp = q->header->succ->data;
    q->header->succ->succ->pred = q->header;
    q->header->succ = q->header->succ->succ;
    q->size--;
    return tmp;
}


static struct tree_stack tree_init_stack()
{
    struct tree_stack s;
    s.elem = malloc(2* sizeof(int*));
    s.capacity =2;
    s.size = 0;
    return s;
}

//扩容
static void expand(struct tree_stack *s)
{
    if(s->size < s->capacity) return; //尚未满员，不必扩容
    s->elem = realloc(s->elem,(s->capacity<<=1)*sizeof(int));
}

static void tree_push(struct tree_stack *s, struct tree_node *e)
{
    expand(s);
    *(s->elem+s->size) = e;
    s->size++;
}

static struct tree_node *tree_pop(struct tree_stack *s)
{
    s->size--;
    return *(s->elem + s->size);
}



struct tree init_tree()
{
    struct tree t;
    t.top = NULL;
    t.size = 0;
    t.hot = NULL;
    
    return t;
}



//层次遍历
void level_traversal(struct tree t,void visit(struct tree_node *e))
{
    struct tree_queue q = tree_init_queue();
    tree_enqueue(&q, t.top->left_child);
    
    while (q.size) {
        struct tree_node *x = tree_dequeue(&q);
        
        visit(x);
        
        if (x->left_child != NULL){
            tree_enqueue(&q, x->left_child);
        }
        
        if (x->right_child != NULL){
            tree_enqueue(&q, x->right_child);
        }
    }
}

void visit_along_left_branch(struct tree_node *x,void visit(struct tree_node *e),struct tree_stack *s)
{
    while (x!= NULL) {
        visit(x);
        tree_push(s,x->right_child);
        x = x->left_child;
    }
}

//先序遍历
void pre_traversal(struct tree t,void visit(struct tree_node *e))
{
    struct tree_stack s = tree_init_stack();
    struct tree_node *x = t.top->left_child;
    while (1) {
        visit_along_left_branch(x,visit,&s);
        if (s.size==0) {
            break;
        }else{
            x = tree_pop(&s);
        }
    }
}

void go_alone_left_branch(struct tree_node *x,struct tree_stack *s)
{
    while (x != NULL) {
        tree_push(s,x);
        x = x->left_child;
    }
}

//中序遍历
void in_traversal(struct tree t,void visit(struct tree_node *e))
{
    struct tree_stack s = tree_init_stack();
    struct tree_node *x = t.top->left_child;
    while (1) {
        go_alone_left_branch(x,&s);
        if (s.size==0) {
            break;
        }else{
            x = tree_pop(&s);
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



void write_tree_to_dotfile(struct tree *t,char opt[],char info[])
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
    print_dot_node(fp ,t->top);
    fprintf(fp, "}\n");
    fclose(fp);
}
