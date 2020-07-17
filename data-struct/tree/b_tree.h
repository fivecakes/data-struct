

#ifndef BTree_h
#define BTree_h

#include "vector.h"
struct BTVector{
    struct BTNode **elem;
    int size;
    int capacity;
};

typedef struct BTVector BTVector;

struct BTNode{
    struct BTNode *parent;
    struct Vector key;
    BTVector child;
};

typedef struct BTNode BTNode;


struct BTree{
    int size;
    int m; //  ⌈m/2⌉ ≤ n+1 < m
    struct BTNode *root;
    struct BTNode *hot;
};

typedef struct BTree BTree;

BTVector btree_vector_init(void);
void btree_vector_insert(BTVector *V, int r, BTNode* e);
void btree_vector_delete(BTVector *V, int r);
BTNode *btree_vector_get(BTVector *V,int r);


BTree btree_init(void);
void btree_insert(BTree *BT,int e);
void btree_remove(BTree *BT,int e);
void writeBTreeToDotFile(BTree *T,char opt[],char info[]);
#endif /* BTree_h */
