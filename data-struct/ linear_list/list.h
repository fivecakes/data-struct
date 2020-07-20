#ifndef list_h
#define list_h

#include "common.h"

struct list_node{
    int data;
    struct list_node *pred;
    struct list_node *succ;
};

struct list{
    int size;
    struct list_node *header;
    struct list_node *trailer;
};


void list_write2dot(struct list L,char opt[],char info[]);
//初始化
struct list list_init(void);

//获取
int list_get(struct list l,int r);

void list_insert_before(struct list_node *p,int e);
//插入
void list_insert(struct list *l, int n, int e);

//选择排序
void list_selection_sort(struct list *l);

//插入排序
void list_insert_sort(struct list *l);


#endif /* list_h */
