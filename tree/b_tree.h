#ifndef b_tree_h
#define b_tree_h

#include "../linear/vector.h"
struct b_tree_vector{
    struct b_tree_node **elem;
    int size;
    int capacity;
};


struct b_tree_node{
    struct b_tree_node *parent;
    struct vector key;
    struct b_tree_vector child;
};


struct b_tree{
    int size;
    int m; //  ⌈m/2⌉ ≤ n+1 < m
    struct b_tree_node *root;
    struct b_tree_node *hot;
};


struct b_tree_vector btree_vector_init(void);
void btree_vector_insert(struct b_tree_vector *v, int r, struct b_tree_node* e);
void btree_vector_delete(struct b_tree_vector *v, int r);
struct b_tree_node *btree_vector_get(struct b_tree_vector *v,int r);


struct b_tree btree_init(void);
void btree_insert(struct b_tree *t,int e);
void btree_remove(struct b_tree *t,int e);
void write_b_tree_to_dotfile(struct b_tree *t,char opt[],char info[]);
#endif
