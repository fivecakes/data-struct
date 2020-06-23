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
    List L1 = initList();
    List L2 = initList();

    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 10; i++) {
            int tmp = rand()%10;
            listInsert(&L1, i, tmp);
            listInsert(&L2, i, tmp);
        }
        writeListToDotFile(L1,"w+","");
    }


    printf("测试选择排序...\n");
    {
        selectionSort(&L1);
        
        writeListToDotFile(L1,"a+","选择排序");
    }

    printf("测试插入排序...\n");
    {
        insertSort(&L2);
        
        writeListToDotFile(L2,"a+","插入排序");
    }
}



