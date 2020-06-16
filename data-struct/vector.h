//
//  vector.h
//  data-struct
//
//  Created by book on 2020/6/15.
//  Copyright © 2020 book. All rights reserved.
//

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

//初始化
static Vector init(void);

//扩容
static void expand(Vector *V);

//插入
static void insert(Vector *V, int r, int e);

//冒泡排序
static void bubbleSort(Vector *V);

//归并排序
static void mergeSort(Vector *V, int lo, int hi);

//二分查找
static int binSearch(Vector V, int e, int lo, int hi);

//插值查找
static int insertValueSearch(Vector V, int e, int lo, int hi);

#endif /* vector_h */
