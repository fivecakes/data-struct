#include "test_vector.h"


//测试用例
void testVector()
{
    Vector V = vector_init();
    Vector V1 = vector_init();
    
    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 30; i++) {
            int tmp =rand()%10;
            vector_insert(&V, i, tmp);
            vector_insert(&V1, i, tmp);
        }
        vector_write2dot(V,"w+","");
    }
    
    
    printf("测试冒泡排序...\n");
    {
        vector_bubble_sort(&V1);
        vector_write2dot(V1,"a+","冒泡排序");
    }
    
    printf("测试归并排序...\n");
    {
        vector_merge_sort(&V,0,V.size);
        vector_write2dot(V,"a+","归并排序");
    }
    
    
    printf("测试二分查找...\n");
    {
        int r0 = vector_bin_search(V,0,0,V.size);
        int r1 = vector_bin_search(V,1,0,V.size);
        int r2 = vector_bin_search(V,9,0,V.size);
        
        printf("%d,%d,%d\n",r0,r1,r2);
    }
    
    printf("测试插值查找...\n");
    {
        int r0 = vector_insert_value_search(V,0,0,V.size);
        int r1 = vector_insert_value_search(V,1,0,V.size);
        int r2 = vector_insert_value_search(V,9,0,V.size);
        printf("%d,%d,%d\n",r0,r1,r2);
    }
}






