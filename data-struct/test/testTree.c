//
//  testTree.c
//  data-struct
//
//  Created by book on 2020/6/23.
//  Copyright © 2020 book. All rights reserved.
//

#include "testTree.h"


void testRedBlack()
{
    printf("测试红黑树...\n");
    {
        Tree T = initBinTree();
        redblack_insert(&T,36);
        redblack_insert(&T,27);
        redblack_insert(&T,58);
        redblack_insert(&T,6);
//        redblack_insert(&T,53);
//        redblack_insert(&T,69);
//        redblack_insert(&T,40);
        writeTreeToDotFile(T,"w+","");
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
        
        btree_insert(&BT,57);
        btree_insert(&BT,152);
        btree_insert(&BT,196);
        btree_insert(&BT,249);
        btree_insert(&BT,266);
        btree_insert(&BT,268);
        btree_insert(&BT,315);
        btree_insert(&BT,423);
        btree_insert(&BT,468);
        btree_insert(&BT,484);
        btree_insert(&BT,528);
        btree_insert(&BT,300);
        btree_insert(&BT,310);
        btree_insert(&BT,299);
        btree_insert(&BT,56);
        btree_insert(&BT,55);
        btree_insert(&BT,54);
        btree_insert(&BT,53);
        btree_insert(&BT,52);
        btree_insert(&BT,51);
        writeBTreeToDotFile(&BT,"w+","");
        btree_remove(&BT,484);
        writeBTreeToDotFile(&BT,"a+","484");
        
        btree_remove(&BT,52);
        writeBTreeToDotFile(&BT,"a+","52");
    }

}
