#ifndef s_play_h
#define s_play_h
#include "bst.h"

struct tree_node *splay_search(struct tree *t,int e);
void splay_insert(struct tree *t,int e);
void splay_remove(struct tree *t,int e);
#endif /* Splay_h */
