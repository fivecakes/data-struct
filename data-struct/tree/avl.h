#ifndef avl_h
#define avl_h
#include "common.h"
#include "bst.h"

struct tree_node *avl_insert(struct tree *T,int e);
void avl_remove(struct tree *T,int e);

#endif /* avl_h */
