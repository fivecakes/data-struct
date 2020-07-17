#include "test_heap.h"


void testHeap()
{
    int a[] = {1,3,5,7,9,2,4,6,8,10};
    Vector V = heapfy(a,10);
    heap_write2dot(&V,"w+","");
    heap_insert(&V, 11);
    heap_insert(&V, 15);
    heap_insert(&V, 20);
    printf("%d\n",heap_get_max(&V));
    heap_del_max(&V);
    heap_write2dot(&V,"w+","");
}
