#ifndef vector_h
#define vector_h

#include "common.h"
struct Vector{
    int *elem;
    int size;
    int capacity;
};

int vector_search(struct Vector *V, int e);
void vector_write2dot(struct Vector V,char opt[],char info[]);
//初始化
struct Vector vector_init(void);

//插入
void vector_insert(struct Vector *V, int r, int e);
void vector_delete(struct Vector *V, int r);
void vector_replace(struct Vector *V, int r, int e);
//冒泡排序
void vector_bubble_sort(struct Vector *V);

//归并排序
void vector_merge_sort(struct Vector *V, int lo, int hi);

//二分查找
int vector_bin_search(struct Vector V, int e, int lo, int hi);

//插值查找
int vector_insert_value_search(struct Vector V, int e, int lo, int hi);

int vector_get(struct Vector *V,int r);

#endif /* vector_h */
