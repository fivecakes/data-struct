#include "heap.h"


int lt(struct vector *v, int i, int p)
{
    if (vector_get(v,i) <= vector_get(v,p)) {
        return 1;
    }else{
        return 0;
    }
}

void swap(struct vector *v, int i, int j)
{
    int tmp;
    tmp = vector_get(v,i);
    vector_replace(v, i, vector_get(v,j));
    vector_replace(v, j, tmp);
}

void percolate_up(struct vector *v,int i)
{
    while (i>0) {
        int p = PARENT(i);
        if(lt(v,i,p)){
            break;
        }else{
            swap(v,i,p);
            i = p;
        }
    }
}


void percolate_down(struct vector *v,int i)
{
    while (1) {
        int lchild = L_CHILD(i);
        int rchild = R_CHILD(i);
        int maxchild;
        
        if (lchild>=v->size && rchild>=v->size) {
            break;
        }else if (lchild>=v->size) {
            maxchild = rchild;
        }else if (rchild>=v->size){
            maxchild = lchild;
        }else if(vector_get(v, lchild) > vector_get(v, rchild)){
            maxchild = lchild;
        }else{
            maxchild = rchild;
        }
        if(vector_get(v, maxchild) > vector_get(v, i)){
            swap(v,i,maxchild);
            i = maxchild;
        }else{
            break;
        }
    }
}


struct vector heapfy(int a[],int len)
{
    struct vector v = vector_init();
    for (int i=0; i<len; i++) {
        vector_insert(&v, v.size, a[i]);
        percolate_up(&v,i);
    }
    return v;
}

void heap_insert(struct vector *v, int e)
{
    int r =v->size;
    vector_insert(v, r, e);
    percolate_up(v,r);
}

int heap_get_max(struct vector *v)
{
    return vector_get(v, 0);
}

int heap_del_max(struct vector *v)
{
    int max = vector_get(v, 0);
    vector_replace(v, 0, vector_get(v, v->size-1));
    v->size--;
    percolate_down(v,0);
    return max;
}



static void print_dot_node(FILE* fp ,struct vector *v,int r)
{
    if (!v) return;
    
    fprintf(fp, " node%d[label=\"%d\"]\n", r,vector_get(v, r));
    
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

void heap_write2dot(struct vector *v,char opt[],char info[])
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
    fprintf(fp, " vector [label=\"{秩 | 值}");
    for (int i = 0; i<v->size; i++) {
        fprintf(fp, "|{%d | %d}",i,*(v->elem+i));
    }
    fprintf(fp, "\"]\n");
    fprintf(fp, "}\n");
    fclose(fp);
}
