#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <stdlib.h>

struct Vector{
    int *elem;
    int size;
    int capacity;
};

typedef struct Vector Vector;

void writeVectorToDotFile(Vector V,char opt[],char info[]);
//初始化
Vector initVector(void);

//扩容
static void expand(Vector *V);

//插入
void insert(Vector *V, int r, int e);

//冒泡排序
void bubbleSort(Vector *V);

//归并排序
void mergeSort(Vector *V, int lo, int hi);

//二分查找
int binSearch(Vector V, int e, int lo, int hi);

//插值查找
int insertValueSearch(Vector V, int e, int lo, int hi);

#endif /* vector_h */
