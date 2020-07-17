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
    string_insert(&S,"dkdfcfcfcfcfcfcfcfcfcfcfcfcfcdmkmfcm");
    
    char P[] = "fcm";
    
    int r1 = string_match(P, S.elem);
    int r2 = string_kmp(P, S.elem);
    int r3 = string_bm(P, S.elem);
    
    printf("manli = %d\n",r1);
    printf("kmp = %d\n",r2);
    printf("bm = %d\n",r3);
}
