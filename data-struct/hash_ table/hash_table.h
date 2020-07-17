#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETCOUNT 17 //表长选素数

struct Hash_entry
{
    char* key;
    char* value;
    struct hashEntry* next;
};


struct Hash_table
{
    struct Hash_entry bucket[BUCKETCOUNT];  //先默认定义16个桶
};



char* find_value_by_key(struct Hash_table* t , char* key);
int insert_entry(struct Hash_table* t , char* key , char* value);
int key2index(char* key);
void init_hash_table(struct Hash_table* t);



#endif /* hash_h */
