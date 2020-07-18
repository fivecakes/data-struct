#include "test_list.h"



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



