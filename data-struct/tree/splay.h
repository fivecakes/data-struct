#ifndef Splay_h
#define Splay_h
#include "bst.h"

struct tree_node *splay_search(struct tree *T,int e);
void splay_insert(struct tree *T,int e);
void splay_remove(struct tree *T,int e);
#endif /* Splay_h */
