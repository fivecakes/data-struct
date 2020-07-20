#include "test_string.h"



void test_string()
{
    struct string s = string_init();
    string_insert(&s,"dkdfcfcfcfcfcfcfcfcfcfcfcfcfcdmkmfcm");
    
    char pa[] = "fcm";
    
    int r1 = string_match(pa, s.elem);
    int r2 = string_kmp(pa, s.elem);
    int r3 = string_bm(pa, s.elem);
    
    printf("manli = %d\n",r1);
    printf("kmp = %d\n",r2);
    printf("bm = %d\n",r3);
}
