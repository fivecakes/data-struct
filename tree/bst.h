#ifndef bst_h
#define bst_h
#include "tree.h"
struct tree_node *bst_succ(struct tree_node *x);
struct tree_node *bst_search(struct tree *t,int e);
struct tree_node *bst_insert(struct tree *t,int e);
void bst_remove(struct tree *t,int e);
struct tree_node *bst_remove_at(struct tree *t,struct tree_node *x);

int bst_update_height(struct tree_node *x);
void bst_update_height_above(struct tree_node *x);
#endif
