#include "test_hash.h"



void print_table(table* t)
{
    int i;
    entry* e;
    if (t == NULL)return;
    for (i = 0; i<BUCKETCOUNT; ++i) {
        printf("\nbucket[%d]:\n" , i);
        e = &(t->bucket[i]);
        while (e->key != NULL) {
            printf("\t%s\t=\t%s\n" , e->key , e->value);
            if (e->next == NULL)break;
            e = e->next;
        }
    }
}


void testHash()
{
    table t;
    init_hash_table(&t);
    
    insert_entry(&t , "aaaa" , "aaaaaaaaaaaaaaaaaa");
    insert_entry(&t , "bbbb" , "bbbbbbbbbbbbbbbbbb");
    insert_entry(&t , "cccc" , "cccccccccccccccccc");

    print_table(&t);
}
