#include "vector.h"


struct vector vector_init()
{
    struct vector v;
    v.elem = malloc(2* sizeof(int));
    v.capacity =2;
    v.size = 0;
    return v;
}


//扩容
static void vector_expand(struct vector *v)
{
    if(v->size < v->capacity) return; //尚未满员，不必扩容
    v->elem = realloc(v->elem,(v->capacity<<=1)*sizeof(int));
}

int vector_get(struct vector *v,int r)
{
    return *(v->elem + r);
}


//插入
void vector_insert(struct vector *v, int r, int e)
{
    vector_expand(v);
    for (int i = v->size; i>r; i--) {
        *(v->elem+i) = *(v->elem+i-1);
    }
    *(v->elem+r) = e;
    v->size++;
}

void vector_push(struct vector *v, int e)
{
    vector_expand(v);
    *(v->elem+v->size) = e;
    v->size++;
}

int vector_pop(struct vector *v)
{
    v->size--;
    return *(v->elem + v->size);
}

//替换
void vector_replace(struct vector *v, int r, int e)
{
    *(v->elem+r) = e;
}

//遍历搜索
int vector_search(struct vector *v, int e)
{
    for (int i = 0; i<v->size; i++) {
        if (*(v->elem+i) > e) {
            return i-1;
        }
    }
    return v->size-1;
}


//删除
void vector_delete(struct vector *v, int r)
{
    for (int i = r; i<v->size -1; i++) {
        *(v->elem+i) = *(v->elem+i+1);
    }
    v->size--;
}

static int bubble(struct vector *v,int lo, int hi)
{
    int last = lo;
    int tmp;
    while (lo < hi) {
        if (*(v->elem+lo) > *(v->elem+lo+1)) {
            tmp =*(v->elem+lo+1);
            *(v->elem+lo+1) = *(v->elem+lo);
            *(v->elem+lo) = tmp;
            last = lo+1;
        }
        lo++;
    }
    return last;
}

void vector_bubble_sort(struct vector *v)
{
    int lo = 0;
    int hi = v->size-1;
    
    while (lo < hi) {
        hi = bubble(v,lo,hi);
    }
}



static void merge(struct vector *v, int lo, int mi, int hi)
{
    int lb = mi - lo;
    int lc = hi - mi;
    
    int *b = malloc(lb * sizeof(int));
    for (int i = 0; i<lb; i++) {
        *(b+i) = *(v->elem+lo+i);
    }
    
    for (int i=0,j=0,k=0; j<lb; ) {
        if (k<lc) {
            if (*(b+j)<*(v->elem+mi+k)) {
                *(v->elem+lo+i) = *(b+j);
                j++;
                i++;
            }else{
                *(v->elem+lo+i) = *(v->elem+mi+k);
                k++;
                i++;
            }
        }else{
            *(v->elem+lo+i) = *(b+j);
            j++;
            i++;
        }
    }
}

void vector_merge_sort(struct vector *v, int lo, int hi)
{
    if (hi - lo <2) {
        return;
    }
    int mi = (lo + hi) >> 1;
    vector_merge_sort(v, lo, mi);
    vector_merge_sort(v, mi, hi);
    merge(v,lo, mi, hi);
}

//二分查找
int vector_bin_search(struct vector v,int e,int lo,int hi)
{
    while (lo<hi) {
        int mi = (lo+hi)>>1;
        
        if(e<*(v.elem+mi)){
            hi = mi;
        }else{
            lo = mi + 1;
        }
    }
    
    return --lo;
}

//插值查找
int vector_insert_value_search(struct vector v,int e,int lo,int hi)
{
    hi--;
    while (lo<hi) {
        int mi = lo + (hi-lo)*(int)(e-*(v.elem+lo))/(*(v.elem+hi)-*(v.elem+lo));
        
        if (mi<lo) {
            return --lo;
        }
        
        if(e<*(v.elem+mi)){
            hi = mi;
        }else{
            lo = mi + 1;
        }
    }
    
    return --lo;
}


void vector_write2dot(struct vector v,char opt[],char info[])
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
    fprintf(fp, " node [shape=\"record\", height=.1]\n");
    fprintf(fp, " vector [label=\"{秩 | 值}");
    for (int i = 0; i<v.size; i++) {
        fprintf(fp, "|{%d | %d}",i,*(v.elem+i));
    }
    fprintf(fp, "\"]\n");
    fprintf(fp, "}\n");
    fclose(fp);
}
