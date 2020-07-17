

#ifndef BTree_h
#define BTree_h

#include "vector.h"
struct BTVector{
    struct BTNode **elem;
    int size;
    int capacity;
};


struct BTNode{
    struct BTNode *parent;
    struct Vector key;
    struct BTVector child;
};


struct BTree{
    int size;
    int m; //  ⌈m/2⌉ ≤ n+1 < m
    struct BTNode *root;
    struct BTNode *hot;
};


struct BTVector btree_vector_init(void);
void btree_vector_insert(struct BTVector *V, int r, struct BTNode* e);
void btree_vector_delete(struct BTVector *V, int r);
struct BTNode *btree_vector_get(struct BTVector *V,int r);


struct BTree btree_init(void);
void btree_insert(struct BTree *BT,int e);
void btree_remove(struct BTree *BT,int e);
void writeBTreeToDotFile(struct BTree *T,char opt[],char info[]);
#endif /* BTree_h */
