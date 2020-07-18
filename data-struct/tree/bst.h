#ifndef BST_h
#define BST_h
#include "tree.h"
struct tree_node *bst_succ(struct tree_node *x);
struct tree_node *bst_search(struct tree *T,int e);
struct tree_node *bst_insert(struct tree *T,int e);
void bst_remove(struct tree *T,int e);
struct tree_node *bst_remove_at(struct tree *T,struct tree_node *x);

int bst_update_height(struct tree_node *x);
void bst_update_height_above(struct tree_node *x);
#endif /* BST_h */
