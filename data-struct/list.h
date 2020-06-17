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
List initList(void);

//获取
int listGet(List L,int r);

void insertBefore(ListNode *p,int e);
//插入
void listInsert(List *L, int n, int e);

//选择排序
void selectionSort(List *L);

//插入排序
void insertSort(List *L);


#endif /* list_h */
