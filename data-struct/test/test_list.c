//
//  testList.c
//  data-struct
//
//  Created by book on 2020/6/23.
//  Copyright © 2020 book. All rights reserved.
//

#include "testList.h"



//测试用例
void testList()
{
    List L1 = list_init();
    List L2 = list_init();

    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 10; i++) {
            int tmp = rand()%10;
            list_insert(&L1, i, tmp);
            list_insert(&L2, i, tmp);
        }
        list_write2dot(L1,"w+","");
    }


    printf("测试选择排序...\n");
    {
        list_selection_sort(&L1);
        
        list_write2dot(L1,"a+","选择排序");
    }

    printf("测试插入排序...\n");
    {
        list_insert_sort(&L2);
        
        list_write2dot(L2,"a+","插入排序");
    }
}



