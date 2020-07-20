#ifndef vector_h
#define vector_h

#include "common.h"
struct vector{
    int *elem;
    int size;
    int capacity;
};

int vector_search(struct vector *V, int e);
void vector_write2dot(struct vector V,char opt[],char info[]);
//初始化
struct vector vector_init(void);

//插入
void vector_push(struct vector *v, int e);
int vector_pop(struct vector *v);
void vector_insert(struct vector *V, int r, int e);
void vector_delete(struct vector *V, int r);
void vector_replace(struct vector *V, int r, int e);
//冒泡排序
void vector_bubble_sort(struct vector *V);

//归并排序
void vector_merge_sort(struct vector *V, int lo, int hi);

//二分查找
int vector_bin_search(struct vector V, int e, int lo, int hi);

//插值查找
int vector_insert_value_search(struct vector V, int e, int lo, int hi);

int vector_get(struct vector *V,int r);

#endif /* vector_h */
