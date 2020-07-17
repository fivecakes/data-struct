#ifndef vector_h
#define vector_h

#include "common.h"
struct Vector{
    int *elem;
    int size;
    int capacity;
};

typedef struct Vector Vector;
int vector_search(Vector *V, int e);
void vector_write2dot(Vector V,char opt[],char info[]);
//初始化
Vector vector_init(void);

//插入
void vector_insert(Vector *V, int r, int e);
void vector_delete(Vector *V, int r);
void vector_replace(Vector *V, int r, int e);
//冒泡排序
void vector_bubble_sort(Vector *V);

//归并排序
void vector_merge_sort(Vector *V, int lo, int hi);

//二分查找
int vector_bin_search(Vector V, int e, int lo, int hi);

//插值查找
int vector_insert_value_search(Vector V, int e, int lo, int hi);

int vector_get(Vector *V,int r);

#endif /* vector_h */
