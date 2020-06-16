//
//  vectorTest.c
//  data-struct
//
//  Created by book on 2020/6/15.
//  Copyright © 2020 book. All rights reserved.
//

#include "vector.h"
#include "vector.c"

static void printVector(Vector V)
{
    for (int i = 0; i<V.size; i++) {
        printf("%d,",*(V.elem+i));
    }
    printf("\n");
}

static void compareWithArray(Vector V,int *arr)
{
    for (int i = 0; i<V.size; i++) {
        if(*(V.elem+i) != arr[i]){
            printf("!!!!!!!!!!!!!!!测试未通过!!!!!!!!!!!!!!!！\n");
            exit(0);
        }
    }
}

//测试用例
static void testVector()
{
    Vector V = init();
    Vector V1 = init();
    
    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 30; i++) {
            int tmp =rand()%10;
            insert(&V, i, tmp);
            insert(&V1, i, tmp);
        }
        printVector(V);
        
        int a[] = {2,1,0,7,9,5,5,5,7,3,5,5,3,6,2,0,3,4,2,8,1,2,0,3,2,4,3,8,7,8};
        compareWithArray(V, a);
    }
    
    
    printf("测试冒泡排序...\n");
    {
        bubbleSort(&V1);
        printVector(V1);
        int a[] = {0,0,0,1,1,2,2,2,2,2,3,3,3,3,3,4,4,5,5,5,5,5,6,7,7,7,8,8,8,9};
        compareWithArray(V1, a);
    }
    
    printf("测试归并排序...\n");
    {
        mergeSort(&V,0,V.size);
        printVector(V);
        int a[] = {0,0,0,1,1,2,2,2,2,2,3,3,3,3,3,4,4,5,5,5,5,5,6,7,7,7,8,8,8,9};
        compareWithArray(V, a);
    }
    
    
    printf("测试二分查找...\n");
    {
        int r0 = binSearch(V,0,0,V.size);
        int r1 = binSearch(V,1,0,V.size);
        int r2 = binSearch(V,9,0,V.size);
        
        printf("%d,%d,%d\n",r0,r1,r2);
        if (r0 != 2 || r1 != 4 || r2 != 29 ) {
            printf("!!!!!!!!!!!!!!!测试未通过!!!!!!!!!!!!!!!！\n");
            exit(0);
        }
    }
    
    printf("测试插值查找...\n");
    {
        int r0 = insertValueSearch(V,0,0,V.size);
        int r1 = insertValueSearch(V,1,0,V.size);
        int r2 = insertValueSearch(V,9,0,V.size);
        printf("%d,%d,%d\n",r0,r1,r2);
        if (r0 != 2 || r1 != 4 || r2 != 29 ) {
            printf("!!!!!!!!!!!!!!!测试未通过!!!!!!!!!!!!!!!！\n");
            exit(0);
        }
    }
}
