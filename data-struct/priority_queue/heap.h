#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "vector.h"


#define Parent(i) ((i-1)>>1)
#define LChild(i) ((i<<1)+1)
#define RChild(i) ((1+i)<<1)


struct Vector heapfy(int a[],int len);
void heap_insert(struct Vector *V, int e);
int heap_get_max(struct Vector *V);
int heap_del_max(struct Vector *V);

void heap_write2dot(struct Vector *V,char opt[],char info[]);
#endif
