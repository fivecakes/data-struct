//
//  testTree.c
//  data-struct
//
//  Created by book on 2020/6/23.
//  Copyright © 2020 book. All rights reserved.
//

#include "testTree.h"

void testBinTree()
{
    Tree T = initBinTree();

    printf("测试二叉树...\n");
    {
        TreeNode *n1 = insertAsLC(T.top, 1);
        TreeNode *n2 = insertAsLC(n1, 2);
        TreeNode *n3 = insertAsRC(n1, 3);
        TreeNode *n4 = insertAsLC(n2, 4);
        TreeNode *n5 = insertAsRC(n2, 5);
        TreeNode *n6 = insertAsLC(n3, 6);
        TreeNode *n7 = insertAsRC(n3, 7);

        writeTreeToDotFile(T,"w+","");
        printf("层次遍历:");
        travLevel(T,visit);
        printf("\n");
        
        printf("先序遍历:");
        travPre(T,visit);
        printf("\n");
        
        printf("中序遍历:");
        travIn(T,visit);
        printf("\n");

    }

}



void testBST()
{

    printf("测试BST...\n");
    {
        Tree T = initBinTree();
        bst_insert(&T,36);
        bst_insert(&T,27);
        bst_insert(&T,58);
        bst_insert(&T,6);
        bst_insert(&T,53);
        bst_insert(&T,69);
        bst_insert(&T,40);
        bst_insert(&T,46);
        bst_insert(&T,64);

        writeTreeToDotFile(T,"w+","");
        bst_remove(&T,69);
        writeTreeToDotFile(T,"a+","remove69");
        bst_remove(&T,36);
        writeTreeToDotFile(T,"a+","remove36");
    }

}

void testAVL()
{

    printf("测试AVL...\n");
    {

        Tree T = initBinTree();
        avl_insert(&T,36);
        avl_insert(&T,27);
        avl_insert(&T,58);
        avl_insert(&T,6);
        avl_insert(&T,53);
        avl_insert(&T,69);
        avl_insert(&T,40);
        writeTreeToDotFile(T,"w+","40");

        avl_insert(&T,46);
        writeTreeToDotFile(T,"a+","46");

        avl_insert(&T,41);
        writeTreeToDotFile(T,"a+","41");
        avl_remove(&T,6);
        
        writeTreeToDotFile(T,"a+","remove6");
    }
}


void testSplay()
{

    printf("测试Splay...\n");
    {

        Tree T = initBinTree();
        avl_insert(&T,36);
        avl_insert(&T,27);
        avl_insert(&T,58);
        avl_insert(&T,6);
        avl_insert(&T,53);
        avl_insert(&T,69);
        avl_insert(&T,40);
        writeTreeToDotFile(T,"w+","40");

        avl_insert(&T,46);
        writeTreeToDotFile(T,"a+","46");

        avl_insert(&T,41);
        writeTreeToDotFile(T,"a+","41");
        avl_remove(&T,6);
        
        writeTreeToDotFile(T,"a+","remove6");
    }
}
