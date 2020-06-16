//
//  listTest.c
//  data-struct
//
//  Created by book on 2020/6/15.
//  Copyright © 2020 book. All rights reserved.
//

#include "list.h"
#include "list.c"


static void printList(List L)
{
    ListNode *p = L.header;
    
    for (int i = 0; i<L.size; i++) {
        p = p->succ;
        printf("%d,",p->data);
    }
    printf("\n");
}

static void listcompareWithArray(List L,int *arr)
{
    ListNode *p = L.header;
    
    for (int i = 0; i<L.size; i++) {
        p = p->succ;
        
        if(p->data != arr[i]){
            printf("!!!!!!!!!!!!!!!测试未通过!!!!!!!!!!!!!!!！\n");
            exit(0);
        }
    }
}

//测试用例
static void testList()
{
    List L1 = initList();
    List L2 = initList();
    
    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 30; i++) {
            int tmp = rand()%10;
            listInsert(&L1, i, tmp);
            listInsert(&L2, i, tmp);
        }
        printList(L1);
        printList(L2);
        
        int a[] = {2,1,0,7,9,5,5,5,7,3,5,5,3,6,2,0,3,4,2,8,1,2,0,3,2,4,3,8,7,8};
        listcompareWithArray(L1, a);
    }
    
    
    printf("测试选择排序...\n");
    {
        selectionSort(&L1);
        printList(L1);
        
        int a[] = {0,0,0,1,1,2,2,2,2,2,3,3,3,3,3,4,4,5,5,5,5,5,6,7,7,7,8,8,8,9};
        listcompareWithArray(L1, a);
    }
    
    printf("测试插入排序...\n");
    {
        insertSort(&L2);
        printList(L2);
        
        int a[] = {0,0,0,1,1,2,2,2,2,2,3,3,3,3,3,4,4,5,5,5,5,5,6,7,7,7,8,8,8,9};
        listcompareWithArray(L2, a);
    }
}
