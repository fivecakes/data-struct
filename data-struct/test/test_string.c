#include "test_string.h"



void test_string()
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
