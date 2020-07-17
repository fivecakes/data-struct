//
//  testHash.c
//  data-struct
//
//  Created by book on 2020/7/7.
//  Copyright © 2020 book. All rights reserved.
//

#include "test_hash.h"



void printTable(table* t)
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
    initHashTable(&t);
    
    insertEntry(&t , "aaaa" , "aaaaaaaaaaaaaaaaaa");
    insertEntry(&t , "bbbb" , "bbbbbbbbbbbbbbbbbb");
    insertEntry(&t , "cccc" , "cccccccccccccccccc");

    printTable(&t);
}
