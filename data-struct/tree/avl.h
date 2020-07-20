#ifndef avl_h
#define avl_h
#include "common.h"
#include "bst.h"

struct tree_node *avl_insert(struct tree *t,int e);
void avl_remove(struct tree *t,int e);

#endif /* avl_h */
