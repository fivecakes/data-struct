#include "test_tree.h"


void test_bst()
{

    printf("测试BST...\n");
    {
        struct tree t = init_tree();
        bst_insert(&t,36);
        bst_insert(&t,27);
        bst_insert(&t,58);
        bst_insert(&t,6);
        bst_insert(&t,53);
        bst_insert(&t,69);
        bst_insert(&t,40);
        bst_insert(&t,46);
        bst_insert(&t,64);
        
        write_tree_to_dotfile(&t,"w+","");
        
        printf("先序遍历:");
        pre_traversal(t,visit);
        printf("\n");
        
        printf("中序遍历:");
        in_traversal(t,visit);
        printf("\n");
        
        printf("层次遍历:");
        level_traversal(t,visit);
        printf("\n");
        
        write_tree_to_dotfile(&t,"w+","");
        bst_remove(&t,69);
        write_tree_to_dotfile(&t,"a+","remove69");
        bst_remove(&t,36);
        write_tree_to_dotfile(&t,"a+","remove36");
    }

}



void test_avl()
{

    printf("测试AVL...\n");
    {

        struct tree T = init_tree();
        avl_insert(&T,36);
        avl_insert(&T,27);
        avl_insert(&T,58);
        avl_insert(&T,6);
        avl_insert(&T,53);
        avl_insert(&T,69);
        avl_insert(&T,40);
        write_tree_to_dotfile(&T,"w+","40");

        avl_insert(&T,46);
        write_tree_to_dotfile(&T,"a+","46");

        avl_insert(&T,41);
        write_tree_to_dotfile(&T,"a+","41");
        avl_remove(&T,6);
        
        write_tree_to_dotfile(&T,"a+","remove6");
    }
}

void test_spaly()
{
    printf("测试Spaly...\n");
    {
        struct tree T = init_tree();
        write_tree_to_dotfile(&T,"w+","");
        splay_insert(&T,36);
        write_tree_to_dotfile(&T,"a+","36");
        
        splay_insert(&T,27);
        write_tree_to_dotfile(&T,"a+","27");
        
        splay_insert(&T,58);
        write_tree_to_dotfile(&T,"a+","58");
        
        splay_insert(&T,6);
        write_tree_to_dotfile(&T,"a+","6");
        
        splay_insert(&T,53);
        write_tree_to_dotfile(&T,"a+","53");
        
        splay_insert(&T,69);
        write_tree_to_dotfile(&T,"a+","69");
        
        splay_insert(&T,40);
        write_tree_to_dotfile(&T,"a+","40");
        
        splay_insert(&T,46);
        write_tree_to_dotfile(&T,"a+","46");
        
        splay_insert(&T,64);
        write_tree_to_dotfile(&T,"a+","64");
        splay_remove(&T,69);
        write_tree_to_dotfile(&T,"a+","remove69");
        splay_search(&T,6);
        write_tree_to_dotfile(&T,"a+","search6");
        splay_search(&T,36);
        write_tree_to_dotfile(&T,"a+","search36");
        splay_search(&T,46);
        write_tree_to_dotfile(&T,"a+","search46");
        splay_search(&T,27);
        write_tree_to_dotfile(&T,"a+","search27");
        splay_remove(&T,58);
        write_tree_to_dotfile(&T,"a+","r58");
    }

}



void test_b_tree()
{
    printf("测试B-Tree...\n");
    {
        struct b_tree BT = btree_init();
        
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
        write_b_tree_to_dotfile(&BT,"w+","");
        btree_remove(&BT,484);
        write_b_tree_to_dotfile(&BT,"a+","484");

        btree_remove(&BT,52);
        write_b_tree_to_dotfile(&BT,"a+","52");
    }

}



void test_red_black()
{
    printf("测试红黑树...\n");
    {
        struct tree t = init_tree();
        redblack_insert(&t,36);
        redblack_insert(&t,27);
        redblack_insert(&t,58);
        redblack_insert(&t,6);
        redblack_insert(&t,53);
        redblack_insert(&t,69);
        redblack_insert(&t,40);
        redblack_insert(&t,41);
        redblack_insert(&t,39);
        redblack_insert(&t,76);
//        redblack_insert(&T,21);
//        redblack_insert(&T,24);
//        redblack_insert(&T,78);
//        redblack_insert(&T,98);
//        redblack_insert(&T,57);
//        redblack_insert(&T,35);
        write_tree_to_dotfile(&t,"w+","");
        //BB-1
//        redblack_remove(&T,6);
//        redblack_remove(&T,39);
//        redblack_remove(&T,40);
//        writeTreeToDotFile(&T,"a+","");
    }
}
