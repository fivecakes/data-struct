#include "test_heap.h"


void test_heap()
{
    struct heap pq = heap_vector_init();
    
    for (int i=10; i>0; i--) {
        struct heap_node hn;
        hn.data = i;
        hn.priority = i;

        heap_insert(&pq, hn);
    }
    printf("%d\n",heap_get_max(&pq).data);
    heap_write2dot(&pq,"w+","");
}
