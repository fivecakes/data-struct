//
//  BTree.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef BTree_h
#define BTree_h

#include <stdio.h>
#include "vector.h"
struct BTVector{
    struct BTNode **elem;
    int size;
    int capacity;
};

typedef struct BTVector BTVector;

struct BTNode{
    struct BTNode *parent;
    Vector key;
    BTVector child;
};

typedef struct BTNode BTNode;


struct BTree{
    int size;
    int order;
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
