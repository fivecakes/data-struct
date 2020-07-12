//
//  testString.c
//  data-struct
//
//  Created by book on 2020/7/12.
//  Copyright © 2020 book. All rights reserved.
//

#include "testString.h"



void testString()
{
    String S = string_init();
    string_insert(&S,"012345");
    string_insert(&S,"6789");
    
    int r = string_match("0123456789", S.elem);
    printf("%d\n",r);
    
    r = string_kmp("0123456789", S.elem);
    printf("%d\n",r);
}
