//
//  testTree.c
//  data-struct
//
//  Created by book on 2020/6/23.
//  Copyright © 2020 book. All rights reserved.
//

#include "testTree.h"

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
        printf("层次遍历:");
        travLevel(T,visit);
        printf("\n");
        
        printf("先序遍历:");
        travPre(T,visit);
        printf("\n");
        
        printf("中序遍历:");
        travIn(T,visit);
        printf("\n");
        
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
        BTree BT = btree_init();
        
        btree_insert(&BT,50);
        btree_insert(&BT,52);
        btree_insert(&BT,54);
        writeBTreeToDotFile(BT,"w+","50,52,54");
        btree_insert(&BT,56);
        btree_insert(&BT,58);
//        btree_insert(&BT,60);
//        btree_insert(&BT,62);
        writeBTreeToDotFile(BT,"a+","");
    }

}
