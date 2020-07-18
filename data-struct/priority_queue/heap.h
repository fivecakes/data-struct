#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "vector.h"


#define Parent(i) ((i-1)>>1)
#define LChild(i) ((i<<1)+1)
#define RChild(i) ((1+i)<<1)


struct vector heapfy(int a[],int len);
void heap_insert(struct vector *V, int e);
int heap_get_max(struct vector *V);
int heap_del_max(struct vector *V);

void heap_write2dot(struct vector *V,char opt[],char info[]);
#endif
