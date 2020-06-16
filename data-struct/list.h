//
//  list.h
//  data-struct
//
//  Created by book on 2020/6/15.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef list_h
#define list_h


#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int data;
    struct ListNode *pred;
    struct ListNode *succ;
};

struct List{
    int size;
    struct ListNode *header;
    struct ListNode *trailer;
};

typedef struct ListNode ListNode;
typedef struct List List;

//初始化
static List initList(void);

//获取
static int listGet(List L,int r);

static void insertBefore(ListNode *p,int e);
//插入
static void listInsert(List *L, int n, int e);

//选择排序
static void selectionSort(List *L);

//插入排序
static void insertSort(List *L);


#endif /* list_h */
