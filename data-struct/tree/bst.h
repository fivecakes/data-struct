#ifndef BST_h
#define BST_h
#include "tree.h"
struct TreeNode *bst_succ(struct TreeNode *x);
struct TreeNode *bst_search(struct Tree *T,int e);
struct TreeNode *bst_insert(struct Tree *T,int e);
void bst_remove(struct Tree *T,int e);
struct TreeNode *bst_remove_at(struct Tree *T,struct TreeNode *x);

int bst_update_height(struct TreeNode *x);
void bst_update_height_above(struct TreeNode *x);
#endif /* BST_h */
