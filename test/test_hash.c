#include "test_hash.h"





void test_hash()
{
    struct hash_table t;
    init_hash_table(&t);
    
    hash_insert(&t , "aaaa" , "aaaaaaaaaaaaaaaaaa");
    hash_insert(&t , "bbbb" , "bbbbbbbbbbbbbbbbbb");
    hash_insert(&t , "cccc" , "cccccccccccccccccc");

    print_hash_table(&t);
}
