#include "vector.h"


Vector vector_init()
{
    Vector V;
    V.elem = malloc(2* sizeof(int));
    V.capacity =2;
    V.size = 0;
    return V;
}


//扩容
static void vector_expand(Vector *V)
{
    if(V->size < V->capacity) return; //尚未满员，不必扩容
    V->elem = realloc(V->elem,(V->capacity<<=1)*sizeof(int));
}

int vector_get(Vector *V,int r)
{
    return *(V->elem + r);
}


//插入
void vector_insert(Vector *V, int r, int e)
{
    vector_expand(V);
    for (int i = V->size; i>r; i--) {
        *(V->elem+i) = *(V->elem+i-1);
    }
    *(V->elem+r) = e;
    V->size++;
}

//遍历搜索
int vector_search(Vector *V, int e)
{
    for (int i = 0; i<V->size; i++) {
        if (*(V->elem+i) > e) {
            return i-1;
        }
    }
    return V->size-1;
}


//删除
void vector_delete(Vector *V, int r)
{
    for (int i = r; i<V->size -1; i++) {
        *(V->elem+i) = *(V->elem+i+1);
    }
    V->size--;
}

static int bubble(Vector *V,int lo, int hi)
{
    int last = lo;
    int tmp;
    while (lo < hi) {
        if (*(V->elem+lo) > *(V->elem+lo+1)) {
            tmp =*(V->elem+lo+1);
            *(V->elem+lo+1) = *(V->elem+lo);
            *(V->elem+lo) = tmp;
            last = lo+1;
        }
        lo++;
    }
    return last;
}

void vector_bubble_sort(Vector *V)
{
    int lo = 0;
    int hi = V->size-1;
    
    while (lo < hi) {
        hi = bubble(V,lo,hi);
    }
}



static void merge(Vector *V, int lo, int mi, int hi)
{
    int lb = mi - lo;
    int lc = hi - mi;
    
    int *b = malloc(lb * sizeof(int));
    for (int i = 0; i<lb; i++) {
        *(b+i) = *(V->elem+lo+i);
    }
    
    for (int i=0,j=0,k=0; j<lb; ) {
        if (k<lc) {
            if (*(b+j)<*(V->elem+mi+k)) {
                *(V->elem+lo+i) = *(b+j);
                j++;
                i++;
            }else{
                *(V->elem+lo+i) = *(V->elem+mi+k);
                k++;
                i++;
            }
        }else{
            *(V->elem+lo+i) = *(b+j);
            j++;
            i++;
        }
    }
}

void vector_merge_sort(Vector *V, int lo, int hi)
{
    if (hi - lo <2) {
        return;
    }
    int mi = (lo + hi) >> 1;
    vector_merge_sort(V, lo, mi);
    vector_merge_sort(V, mi, hi);
    merge(V,lo, mi, hi);
}

//二分查找
int vector_bin_search(Vector V,int e,int lo,int hi)
{
    while (lo<hi) {
        int mi = (lo+hi)>>1;
        
        if(e<*(V.elem+mi)){
            hi = mi;
        }else{
            lo = mi + 1;
        }
    }
    
    return --lo;
}

//插值查找
int vector_insert_value_search(Vector V,int e,int lo,int hi)
{
    hi--;
    while (lo<hi) {
        int mi = lo + (hi-lo)*(int)(e-*(V.elem+lo))/(*(V.elem+hi)-*(V.elem+lo));
        
        if (mi<lo) {
            return --lo;
        }
        
        if(e<*(V.elem+mi)){
            hi = mi;
        }else{
            lo = mi + 1;
        }
    }
    
    return --lo;
}


void vector_write2dot(Vector V,char opt[],char info[])
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
    fprintf(fp, " node [shape=\"record\", height=.1]\n");
    fprintf(fp, " vector [label=\"{秩 | 值}");
    for (int i = 0; i<V.size; i++) {
        fprintf(fp, "|{%d | %d}",i,*(V.elem+i));
    }
    fprintf(fp, "\"]\n");
    fprintf(fp, "}\n");
    fclose(fp);
}
