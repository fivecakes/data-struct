#ifndef BST_h
#define BST_h
#include "tree.h"
TreeNode *bst_succ(TreeNode *x);
TreeNode *bst_search(Tree *T,int e);
TreeNode *bst_insert(Tree *T,int e);
void bst_remove(Tree *T,int e);
TreeNode *bst_remove_at(Tree *T,TreeNode *x);

int bst_update_height(TreeNode *x);
void bst_update_height_above(TreeNode *x);
#endif /* BST_h */
