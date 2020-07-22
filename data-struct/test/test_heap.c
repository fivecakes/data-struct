#include "test_heap.h"


void test_heap()
{
    struct heap pq = heap_vector_init();
    
    for (int i=10; i>0; i--) {
        heap_insert(&pq, i,i);
    }
    
    printf("%d\n",heap_get_max(&pq).data);
    heap_write2dot(&pq,"w+","");
}
