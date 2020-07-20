#include "test_heap.h"


void test_heap()
{
    int a[] = {1,3,5,7,9,2,4,6,8,10};
    struct vector v = heapfy(a,10);
    heap_write2dot(&v,"w+","");
    heap_insert(&v, 11);
    heap_insert(&v, 15);
    heap_insert(&v, 20);
    printf("%d\n",heap_get_max(&v));
    heap_del_max(&v);
    heap_write2dot(&v,"w+","");
}
