#ifndef red_black_tree_h
#define red_black_tree_h

#include "bst.h"



struct tree_node *redblack_insert(struct tree *t,int e);
void redblack_remove(struct tree *t,int e);

#endif
