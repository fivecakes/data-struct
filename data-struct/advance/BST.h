//
//  BST.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include "binTree.h"

BinNode *bst_search_parent(BinTree *T,int e);
BinNode *bst_insert(BinTree *T,int e);
void bst_remove(BinTree *T,int e);
void bst_remove_at(BinNode **ptc,BinNode *xp,BinNode *x);

#endif /* BST_h */
