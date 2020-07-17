#ifndef avl_h
#define avl_h
#include "common.h"
#include "bst.h"

struct TreeNode *avl_insert(struct Tree *T,int e);
void avl_remove(struct Tree *T,int e);

#endif /* avl_h */
