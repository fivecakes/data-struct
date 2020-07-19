#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETCOUNT 17 //表长选素数

struct hash_entry
{
    char* key;
    char* value;
    struct hash_entry* next;
};


struct hash_table
{
    struct hash_entry bucket[BUCKETCOUNT];  //先默认定义16个桶
};



char* hash_get(struct hash_table* t , char* key);
int hash_insert(struct hash_table* t , char* key , char* value);
int key2index(char* key);
void init_hash_table(struct hash_table* t);



#endif /* hash_h */
