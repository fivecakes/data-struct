#include "testVector.h"


//测试用例
void testVector()
{
    Vector V = initVector();
    Vector V1 = initVector();
    
    printf("测试插入...\n");
    {
        srand(123456);
        for(int i = 0; i < 30; i++) {
            int tmp =rand()%10;
            insert(&V, i, tmp);
            insert(&V1, i, tmp);
        }
        writeVectorToDotFile(V,"w+","");
    }
    
    
    printf("测试冒泡排序...\n");
    {
        bubbleSort(&V1);
        writeVectorToDotFile(V1,"a+","冒泡排序");
    }
    
    printf("测试归并排序...\n");
    {
        mergeSort(&V,0,V.size);
        writeVectorToDotFile(V,"a+","归并排序");
    }
    
    
    printf("测试二分查找...\n");
    {
        int r0 = binSearch(V,0,0,V.size);
        int r1 = binSearch(V,1,0,V.size);
        int r2 = binSearch(V,9,0,V.size);
        
        printf("%d,%d,%d\n",r0,r1,r2);
    }
    
    printf("测试插值查找...\n");
    {
        int r0 = insertValueSearch(V,0,0,V.size);
        int r1 = insertValueSearch(V,1,0,V.size);
        int r2 = insertValueSearch(V,9,0,V.size);
        printf("%d,%d,%d\n",r0,r1,r2);
    }
}






