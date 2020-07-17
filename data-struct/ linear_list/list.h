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


void list_write2dot(struct List L,char opt[],char info[]);
//初始化
struct List list_init(void);

//获取
int list_get(struct List L,int r);

void list_insert_before(struct ListNode *p,int e);
//插入
void list_insert(struct List *L, int n, int e);

//选择排序
void list_selection_sort(struct List *L);

//插入排序
void list_insert_sort(struct List *L);


#endif /* list_h */
