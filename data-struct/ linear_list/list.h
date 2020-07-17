#ifndef list_h
#define list_h

#include "common.h"

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

void list_write2dot(List L,char opt[],char info[]);
//初始化
List list_init(void);

//获取
int list_get(List L,int r);

void list_insert_before(ListNode *p,int e);
//插入
void list_insert(List *L, int n, int e);

//选择排序
void list_selection_sort(List *L);

//插入排序
void list_insert_sort(List *L);


#endif /* list_h */
