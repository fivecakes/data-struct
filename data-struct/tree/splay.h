#ifndef Splay_h
#define Splay_h
#include "bst.h"

struct TreeNode *splay_search(struct Tree *T,int e);
void splay_insert(struct Tree *T,int e);
void splay_remove(struct Tree *T,int e);
#endif /* Splay_h */
