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



void testSpaly()
{
    printf("测试Spaly...\n");
    {
        Tree T = initBinTree();
        writeTreeToDotFile(T,"w+","");
        splay_insert(&T,36);
        writeTreeToDotFile(T,"a+","36");
        
        splay_insert(&T,27);
        writeTreeToDotFile(T,"a+","27");
        
        splay_insert(&T,58);
        writeTreeToDotFile(T,"a+","58");
        
        splay_insert(&T,6);
        writeTreeToDotFile(T,"a+","6");
        
        splay_insert(&T,53);
        writeTreeToDotFile(T,"a+","53");
        
        splay_insert(&T,69);
        writeTreeToDotFile(T,"a+","69");
        
        splay_insert(&T,40);
        writeTreeToDotFile(T,"a+","40");
        
        splay_insert(&T,46);
        writeTreeToDotFile(T,"a+","46");
        
        splay_insert(&T,64);
        writeTreeToDotFile(T,"a+","64");
        splay_remove(&T,69);
        writeTreeToDotFile(T,"a+","remove69");
        splay_search(&T,6);
        writeTreeToDotFile(T,"a+","search6");
        splay_search(&T,36);
        writeTreeToDotFile(T,"a+","search36");
        splay_search(&T,46);
        writeTreeToDotFile(T,"a+","search46");
        splay_search(&T,27);
        writeTreeToDotFile(T,"a+","search27");
        splay_remove(&T,58);
        writeTreeToDotFile(T,"a+","r58");
    }

}



void testBTree()
{
    printf("测试B-Tree...\n");
    {
        //
        BTNode BTNode1;
        Vector key1 = initVector();
        insert(&key1, key1.size, 28);
        BTVector child1 = btree_init_vector();
        btree_insert(&child1, child1.size, NULL);
        btree_insert(&child1, child1.size, NULL);
        BTNode1.key = key1;
        BTNode1.child = child1;
        //
        BTNode BTNode2;
        Vector key2 = initVector();
        insert(&key2, key2.size, 37);
        insert(&key2, key2.size, 40);
        insert(&key2, key2.size, 41);
        BTVector child2 = btree_init_vector();
        btree_insert(&child2, child2.size, NULL);
        btree_insert(&child2, child2.size, NULL);
        btree_insert(&child2, child2.size, NULL);
        btree_insert(&child2, child2.size, NULL);
        BTNode2.key = key2;
        BTNode2.child = child2;
        //
        BTNode BTNode3;
        Vector key3 = initVector();
        insert(&key3, key3.size, 46);
        BTVector child3 = btree_init_vector();
        btree_insert(&child3, child3.size, NULL);
        btree_insert(&child3, child3.size, NULL);
        BTNode3.key = key3;
        BTNode3.child = child3;
        //
        BTNode BTNode4;
        Vector key4 = initVector();
        insert(&key4, key4.size, 52);
        BTVector child4 = btree_init_vector();
        btree_insert(&child4, child4.size, NULL);
        btree_insert(&child4, child4.size, NULL);
        BTNode4.key = key4;
        BTNode4.child = child4;
        //
        BTNode BTNode5;
        Vector key5 = initVector();
        insert(&key5, key5.size, 34);
        insert(&key5, key5.size, 43);
        insert(&key5, key5.size, 49);
        BTVector child5 = btree_init_vector();
        btree_insert(&child5, child5.size, &BTNode1);
        btree_insert(&child5, child5.size, &BTNode2);
        btree_insert(&child5, child5.size, &BTNode3);
        btree_insert(&child5, child5.size, &BTNode4);
        BTNode5.key = key5;
        BTNode5.child = child5;
        
        BTree BT;
        BT.root = &BTNode5;
        writeBTreeToDotFile(BT,"w+","");
    }

}
