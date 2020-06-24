//
//  BST.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include "Tree.h"
TreeNode *bst_succ(TreeNode *x);
TreeNode *bst_search_parent(Tree *T,int e);
TreeNode *bst_insert(Tree *T,int e);
void bst_remove(Tree *T,int e);
void bst_remove_at(TreeNode **ptc,TreeNode *xp,TreeNode *x);

#endif /* BST_h */
