#ifndef string_h
#define string_h
#include "common.h"
#include <string.h>

struct string{
    char *elem;
    int size;
    int capacity;
};



struct string string_init(void);
void string_insert(struct string *string, char *s);
int string_match(char *p, char *t);
int string_kmp(char *p, char *t);
int string_bm(char *p,char* t);
#endif /* string_h */
