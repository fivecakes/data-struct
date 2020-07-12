//
//  string.h
//  data-struct
//
//  Created by book on 2020/7/12.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef string_h
#define string_h

#include "commom.h"
#include<string.h>


struct String{
    char *elem;
    int size;
    int capacity;
};

typedef struct String String;


String string_init(void);
void string_insert(String *S, char *s);
int string_match(char *P, char *T);
int string_kmp(char *P, char *T);
#endif /* string_h */
