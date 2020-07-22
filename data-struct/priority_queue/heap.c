#include "heap.h"

/**
 优先级越小越优先
 */

struct heap heap_vector_init()
{
    struct heap v;
    v.elem = malloc(2* sizeof(struct heap_node));
    v.capacity =2;
    v.size = 0;
    return v;
}

//扩容
static void heap_vector_expand(struct heap *v)
{
    if(v->size < v->capacity) return; //尚未满员，不必扩容
    v->elem = realloc(v->elem,(v->capacity<<=1)*sizeof(struct heap_node));
}

static struct heap_node heap_vector_get(struct heap *v,int r)
{
    return *(v->elem + r);
}


//插入
static void heap_vector_insert(struct heap *v, int r, struct heap_node e)
{
    heap_vector_expand(v);
    for (int i = v->size; i>r; i--) {
        *(v->elem+i) = *(v->elem+i-1);
    }
    *(v->elem+r) = e;
    v->size++;
}

//替换
static void heap_vector_replace(struct heap *v, int r, struct heap_node e)
{
    *(v->elem+r) = e;
}

static int lt(struct heap *v, int i, int p)
{
    if (heap_vector_get(v,i).priority < heap_vector_get(v,p).priority) {
        return 1;
    }else{
        return 0;
    }
}

static void swap(struct heap *v, int i, int j)
{
    struct heap_node tmp;
    tmp = heap_vector_get(v,i);
    heap_vector_replace(v, i, heap_vector_get(v,j));
    heap_vector_replace(v, j, tmp);
}

static void percolate_up(struct heap *v,int i)
{
    while (i>0) {
        int p = PARENT(i);
        if(lt(v,i,p)){
            swap(v,i,p);
            i = p;
        }else{
            break;
        }
    }
}


static void percolate_down(struct heap *v,int i)
{
    while (1) {
        int lchild = L_CHILD(i);
        int rchild = R_CHILD(i);
        int select;
        
        if (lchild>=v->size && rchild>=v->size) {//没孩子,不用下溢了
            break;
        }else if (rchild>=v->size){//如果没有右孩子，选择左孩子
            select = lchild;
        }else if(heap_vector_get(v, lchild).priority < heap_vector_get(v, rchild).priority){//选择优先级数小的
            select = lchild;
        }else{
            select = rchild;
        }
        
        //如果选择的孩子优先级数小，与之交换
        if(heap_vector_get(v, select).priority < heap_vector_get(v, i).priority){
            swap(v,i,select);
            i = select;
        }else{
            break;
        }
    }
}



void heap_insert(struct heap *v, int data,int priority)
{
    int r =v->size;
    
    struct heap_node hn;
    hn.data = data;
    hn.priority =priority;
    
    heap_vector_insert(v, r, hn);
    percolate_up(v,r);
}

struct heap_node heap_get_min(struct heap *v)
{
    return heap_vector_get(v, 0);
}

struct heap_node heap_del_min(struct heap *v)
{
    struct heap_node min = heap_vector_get(v, 0);
    heap_vector_replace(v, 0, heap_vector_get(v, v->size-1));
    v->size--;
    percolate_down(v,0);
    return min;
}



static void print_dot_node(FILE* fp ,struct heap *v,int r)
{
    if (!v) return;
    
    fprintf(fp, " node%d[label=\"%d\"]\n", r,heap_vector_get(v, r).priority);
    
    int lchild = L_CHILD(r);
    int rchild = R_CHILD(r);
    
    if (lchild>=v->size && rchild>=v->size) {
        return;
    }
    
    if (lchild<v->size) {
        fprintf(fp, " node%d -> node%d\n", r ,lchild) ;
        fprintf(fp, " node%d -> node%d\n", lchild,r) ;
        print_dot_node(fp ,v,lchild);
    }else{
        fprintf(fp, " lChild%d [label=\"Null\"][style = dotted]\n", r);
        fprintf(fp, " node%d -> lChild%d[style = dotted]\n", r,r);
    }
    
    if (rchild<v->size) {
        fprintf(fp, " node%d -> node%d\n", r ,rchild) ;
        fprintf(fp, " node%d -> node%d\n", rchild,r) ;
        print_dot_node(fp ,v,rchild);
    }else{
        fprintf(fp, " rChild%d [label=\"Null\"][style = dotted]\n", r);
        fprintf(fp, " node%d -> rChild%d[style = dotted]\n", r,r);
    }
}

void heap_write2dot(struct heap *v,char opt[],char info[])
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
    
    //完全二叉树
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [style=filled,color=lightblue;];\n\n");
    print_dot_node(fp,v,0);
    
    //下面是向量
    fprintf(fp, " node [shape=\"record\", style=Null,height=.1]\n");
    fprintf(fp, " heap_vector [label=\"{秩 | 值}");
    for (int i = 0; i<v->size; i++) {
        fprintf(fp, "|{%d | %d}",i,(v->elem+i)->priority);
    }
    fprintf(fp, "\"]\n");
    fprintf(fp, "}\n");
    fclose(fp);
}
