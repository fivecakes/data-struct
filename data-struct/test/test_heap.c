#include "test_heap.h"


void test_heap()
{
    struct heap pq = heap_vector_init();
    
    for (int i=10; i>0; i--) {
        heap_insert(&pq, i,i);
    }
    
    //heap_del_min(&pq);
    heap_write2dot(&pq,"w+","");
}
