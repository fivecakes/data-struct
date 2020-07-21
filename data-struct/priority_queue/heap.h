#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "common.h"

struct heap_node{
    int data;
    int priority;
};

struct heap{
    struct heap_node *elem;
    int size;
    int capacity;
};

#define PARENT(i) ((i-1)>>1)
#define L_CHILD(i) ((i<<1)+1)
#define R_CHILD(i) ((1+i)<<1)

struct heap heap_vector_init(void);
void heap_insert(struct heap *v, struct heap_node e);
struct heap_node heap_get_max(struct heap *v);
struct heap_node heap_del_max(struct heap *v);
void heap_write2dot(struct heap *v,char opt[],char info[]);

#endif
