#include "heap.h"


int lt(struct Vector *V, int i, int p)
{
    if (vector_get(V,i) <= vector_get(V,p)) {
        return 1;
    }else{
        return 0;
    }
}

void swap(struct Vector *V, int i, int j)
{
    int tmp;
    tmp = vector_get(V,i);
    vector_replace(V, i, vector_get(V,j));
    vector_replace(V, j, tmp);
}

void percolate_up(struct Vector *V,int i)
{
    while (i>0) {
        int p = Parent(i);
        if(lt(V,i,p)){
            break;
        }else{
            swap(V,i,p);
            i = p;
        }
    }
}


void percolate_down(struct Vector *V,int i)
{
    while (1) {
        int lchild = LChild(i);
        int rchild = RChild(i);
        int maxchild;
        
        if (lchild>=V->size && rchild>=V->size) {
            break;
        }else if (lchild>=V->size) {
            maxchild = rchild;
        }else if (rchild>=V->size){
            maxchild = lchild;
        }else if(vector_get(V, lchild) > vector_get(V, rchild)){
            maxchild = lchild;
        }else{
            maxchild = rchild;
        }
        if(vector_get(V, maxchild) > vector_get(V, i)){
            swap(V,i,maxchild);
            i = maxchild;
        }else{
            break;
        }
    }
}


struct Vector heapfy(int a[],int len)
{
    struct Vector V = vector_init();
    for (int i=0; i<len; i++) {
        vector_insert(&V, V.size, a[i]);
        percolate_up(&V,i);
    }
    return V;
}

void heap_insert(struct Vector *V, int e)
{
    int r =V->size;
    vector_insert(V, r, e);
    percolate_up(V,r);
}

int heap_get_max(struct Vector *V)
{
    return vector_get(V, 0);
}

int heap_del_max(struct Vector *V)
{
    int max = vector_get(V, 0);
    vector_replace(V, 0, vector_get(V, V->size-1));
    V->size--;
    percolate_down(V,0);
    return max;
}



static void printDotNode(FILE* fp ,struct Vector *V,int r)
{
    if (!V) return;
    
    fprintf(fp, " node%d[label=\"%d\"]\n", r,vector_get(V, r));
    
    int lchild = LChild(r);
    int rchild = RChild(r);
    
    if (lchild>=V->size && rchild>=V->size) {
        return;
    }
    
    if (lchild<V->size) {
        fprintf(fp, " node%d -> node%d\n", r ,lchild) ;
        fprintf(fp, " node%d -> node%d\n", lchild,r) ;
        printDotNode(fp ,V,lchild);
    }else{
        fprintf(fp, " lChild%d [label=\"Null\"][style = dotted]\n", r);
        fprintf(fp, " node%d -> lChild%d[style = dotted]\n", r,r);
    }
    
    if (rchild<V->size) {
        fprintf(fp, " node%d -> node%d\n", r ,rchild) ;
        fprintf(fp, " node%d -> node%d\n", rchild,r) ;
        printDotNode(fp ,V,rchild);
    }else{
        fprintf(fp, " rChild%d [label=\"Null\"][style = dotted]\n", r);
        fprintf(fp, " node%d -> rChild%d[style = dotted]\n", r,r);
    }
}

void heap_write2dot(struct Vector *V,char opt[],char info[])
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
    
    //完全二叉树
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [style=filled,color=lightblue;];\n\n");
    printDotNode(fp,V,0);
    
    //下面是向量
    fprintf(fp, " node [shape=\"record\", style=Null,height=.1]\n");
    fprintf(fp, " vector [label=\"{秩 | 值}");
    for (int i = 0; i<V->size; i++) {
        fprintf(fp, "|{%d | %d}",i,*(V->elem+i));
    }
    fprintf(fp, "\"]\n");
    fprintf(fp, "}\n");
    fclose(fp);
}
