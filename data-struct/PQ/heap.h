#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "vector.h"


#define Parent(i) ((i-1)>>1)
#define LChild(i) ((i<<1)+1)
#define RChild(i) ((1+i)<<1)


Vector heapfy(int a[],int len);
void heap_insert(Vector *V, int e);
int heap_get_max(Vector *V);
int heap_del_max(Vector *V);

void heap_write2dot(Vector *V,char opt[],char info[]);
#endif
