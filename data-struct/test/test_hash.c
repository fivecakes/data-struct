#include "test_hash.h"



void print_table(struct hash_table* t)
{
    int i;
    struct hash_entry* e;
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
    struct hash_table t;
    init_hash_table(&t);
    
    hash_insert(&t , "aaaa" , "aaaaaaaaaaaaaaaaaa");
    hash_insert(&t , "bbbb" , "bbbbbbbbbbbbbbbbbb");
    hash_insert(&t , "cccc" , "cccccccccccccccccc");

    print_table(&t);
}
