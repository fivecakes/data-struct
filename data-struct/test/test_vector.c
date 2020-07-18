#include "test_vector.h"


//测试用例
void test_vector()
{
    struct vector v = vector_init();
    struct vector v1 = vector_init();
    
    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 30; i++) {
            int tmp =rand()%10;
            vector_insert(&v, i, tmp);
            vector_insert(&v1, i, tmp);
        }
        vector_write2dot(v,"w+","");
    }
    
    
    printf("测试冒泡排序...\n");
    {
        vector_bubble_sort(&v1);
        vector_write2dot(v1,"a+","冒泡排序");
    }
    
    printf("测试归并排序...\n");
    {
        vector_merge_sort(&v,0,v.size);
        vector_write2dot(v,"a+","归并排序");
    }
    
    
    printf("测试二分查找...\n");
    {
        int r0 = vector_bin_search(v,0,0,v.size);
        int r1 = vector_bin_search(v,1,0,v.size);
        int r2 = vector_bin_search(v,9,0,v.size);
        
        printf("%d,%d,%d\n",r0,r1,r2);
    }
    
    printf("测试插值查找...\n");
    {
        int r0 = vector_insert_value_search(v,0,0,v.size);
        int r1 = vector_insert_value_search(v,1,0,v.size);
        int r2 = vector_insert_value_search(v,9,0,v.size);
        printf("%d,%d,%d\n",r0,r1,r2);
    }
}






