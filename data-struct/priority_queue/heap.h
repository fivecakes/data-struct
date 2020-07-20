#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "vector.h"


#define PARENT(i) ((i-1)>>1)
#define L_CHILD(i) ((i<<1)+1)
#define R_CHILD(i) ((1+i)<<1)


struct vector heapfy(int a[],int len);
void heap_insert(struct vector *v, int e);
int heap_get_max(struct vector *v);
int heap_del_max(struct vector *v);

void heap_write2dot(struct vector *v,char opt[],char info[]);
#endif
