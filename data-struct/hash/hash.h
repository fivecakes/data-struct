//
//  hash.h
//  data-struct
//
//  Created by book on 2020/7/7.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETCOUNT 17 //表长选素数

struct hashEntry
{
    char* key;
    char* value;
    struct hashEntry* next;
};

typedef struct hashEntry entry;

struct hashTable
{
    entry bucket[BUCKETCOUNT];  //先默认定义16个桶
};

typedef struct hashTable table;


char* findValueByKey(table* t , char* key);
int insertEntry(table* t , char* key , char* value);
int key2index(char* key);
void initHashTable(table* t);



#endif /* hash_h */
