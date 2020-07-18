#include "test_linear_list.h"


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


//测试用例
void test_list()
{
    struct list l1 = list_init();
    struct list l2 = list_init();

    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 10; i++) {
            int tmp = rand()%10;
            list_insert(&l1, i, tmp);
            list_insert(&l2, i, tmp);
        }
        list_write2dot(l1,"w+","");
    }


    printf("测试选择排序...\n");
    {
        list_selection_sort(&l1);
        
        list_write2dot(l1,"a+","选择排序");
    }

    printf("测试插入排序...\n");
    {
        list_insert_sort(&l2);
        
        list_write2dot(l2,"a+","插入排序");
    }
}
