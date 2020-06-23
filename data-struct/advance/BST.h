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

TreeNode *bst_search_parent(BinTree *T,int e);
TreeNode *bst_insert(BinTree *T,int e);
void bst_remove(BinTree *T,int e);
void bst_remove_at(TreeNode **ptc,TreeNode *xp,TreeNode *x);

#endif /* BST_h */
