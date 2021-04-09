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

        struct tree t = init_tree();
        avl_insert(&t,36);
        avl_insert(&t,27);
        avl_insert(&t,58);
        avl_insert(&t,6);
        avl_insert(&t,53);
        avl_insert(&t,69);
        avl_insert(&t,40);
        write_tree_to_dotfile(&t,"w+","40");

        avl_insert(&t,46);
        write_tree_to_dotfile(&t,"a+","46");

        avl_insert(&t,41);
        write_tree_to_dotfile(&t,"a+","41");
        avl_remove(&t,6);
        
        write_tree_to_dotfile(&t,"a+","remove6");
    }
}

void test_spaly()
{
    printf("测试Spaly...\n");
    {
        struct tree tree = init_tree();
        write_tree_to_dotfile(&tree,"w+","");
        splay_insert(&tree,36);
        write_tree_to_dotfile(&tree,"a+","36");
        
        splay_insert(&tree,27);
        write_tree_to_dotfile(&tree,"a+","27");
        
        splay_insert(&tree,58);
        write_tree_to_dotfile(&tree,"a+","58");
        
        splay_insert(&tree,6);
        write_tree_to_dotfile(&tree,"a+","6");
        
        splay_insert(&tree,53);
        write_tree_to_dotfile(&tree,"a+","53");
        
        splay_insert(&tree,69);
        write_tree_to_dotfile(&tree,"a+","69");
        
        splay_insert(&tree,40);
        write_tree_to_dotfile(&tree,"a+","40");
        
        splay_insert(&tree,46);
        write_tree_to_dotfile(&tree,"a+","46");
        
        splay_insert(&tree,64);
        write_tree_to_dotfile(&tree,"a+","64");
        splay_remove(&tree,69);
        write_tree_to_dotfile(&tree,"a+","remove69");
        splay_search(&tree,6);
        write_tree_to_dotfile(&tree,"a+","search6");
        splay_search(&tree,36);
        write_tree_to_dotfile(&tree,"a+","search36");
        splay_search(&tree,46);
        write_tree_to_dotfile(&tree,"a+","search46");
        splay_search(&tree,27);
        write_tree_to_dotfile(&tree,"a+","search27");
        splay_remove(&tree,58);
        write_tree_to_dotfile(&tree,"a+","r58");
    }

}



void test_b_tree()
{
    printf("测试B-Tree...\n");
    {
        struct b_tree b_tree = btree_init();
        
        btree_insert(&b_tree,57);
        btree_insert(&b_tree,152);
        btree_insert(&b_tree,196);
        btree_insert(&b_tree,249);
        btree_insert(&b_tree,266);
        btree_insert(&b_tree,268);
        btree_insert(&b_tree,315);
        btree_insert(&b_tree,423);
        btree_insert(&b_tree,468);
        btree_insert(&b_tree,484);
        btree_insert(&b_tree,528);
        btree_insert(&b_tree,300);
        btree_insert(&b_tree,310);
        btree_insert(&b_tree,299);
        btree_insert(&b_tree,56);
        btree_insert(&b_tree,55);
        btree_insert(&b_tree,54);
        btree_insert(&b_tree,53);
        btree_insert(&b_tree,52);
        btree_insert(&b_tree,51);
        write_b_tree_to_dotfile(&b_tree,"w+","");
        btree_remove(&b_tree,484);
        write_b_tree_to_dotfile(&b_tree,"a+","484");

        btree_remove(&b_tree,52);
        write_b_tree_to_dotfile(&b_tree,"a+","52");
    }

}


