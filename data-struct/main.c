#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "binTree.h"
#include "graph.h"
#include "BST.h"

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

static void printStack(Stack V)
{
    for (int i = 0; i<V.size; i++) {
        printf("%d,",*(V.elem+i));
    }
    printf("\n");
}

static void testStack()
{
    Stack S = initStack();
    
    printf("测试栈...\n");
    {
        srand(123456);
        push(&S, 1);
        push(&S, 2);
        push(&S, 3);
        push(&S, 4);
        printStack(S);
        printf("%d\n",pop(&S));
        printf("%d\n",pop(&S));
        printStack(S);
    }
}

static void printQueue(Queue L)
{
    QueueNode *p = L.header;
    
    for (int i = 0; i<L.size; i++) {
        p = p->succ;
        printf("%d,",p->data);
    }
    printf("\n");
}

static void testQueue()
{
    Queue Q = initQueue();
    
    printf("测试队列...\n");
    {
        srand(123456);
        enqueue(&Q, 1);
        enqueue(&Q, 2);
        enqueue(&Q, 3);
        enqueue(&Q, 4);
        printQueue(Q);
        printf("%d\n",dequeue(&Q));
        printf("%d\n",dequeue(&Q));
        printQueue(Q);
    }
}






static void testBinTree()
{
    BinTree T = initBinTree(1);
    
    printf("测试二叉树...\n");
    {
        BinNode *n2 = insertAsLC(T.root, 2);
        BinNode *n3 = insertAsRC(T.root, 3);
        BinNode *n4 = insertAsLC(n2, 4);
        BinNode *n5 = insertAsRC(n2, 5);
        BinNode *n6 = insertAsLC(n3, 6);
        BinNode *n7 = insertAsRC(n3, 7);
        
        TGprint(T);
        travLevel(T,visit);
        printf("\n");
        travPre(T,visit);
        printf("\n");
        travIn(T,visit);
        printf("\n");
        
    }
    
}



void testGraph()
{
    int arr[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,1},
        {0,1,1,0,0},
        {0,1,0,1,0}
    };
    Graph G = initGraph(arr);
    dfs(&G);
    printf("\n");
}

static void testBST()
{
    
    printf("测试BST...\n");
    {
        BinTree T;
        T.root = NULL;
        bst_insert(&T,36);
        bst_insert(&T,27);
        bst_insert(&T,58);
        bst_insert(&T,6);
        bst_insert(&T,53);
        bst_insert(&T,69);
        bst_insert(&T,40);
        bst_insert(&T,46);
        bst_insert(&T,64);
        
        
        travIn(T,visit);
        printf("\n");
        bst_delete(&T,69);
        travIn(T,visit);
        printf("\n");
        bst_delete(&T,36);
        travIn(T,visit);
        printf("\n");
    }
    
}
int main()
{
//    testVector();
//    testList();
//    testStack();
//    testQueue();
    //testBinTree();
//    testGraph();
    testBST();

}
