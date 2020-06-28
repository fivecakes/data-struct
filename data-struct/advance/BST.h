//
//  BST.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef BST_h
#define BST_h
#include "commom.h"
#include "Tree.h"
TreeNode *bst_succ(TreeNode *x);
TreeNode *bst_search(Tree *T,int e);
TreeNode *bst_insert(Tree *T,int e);
void bst_remove(Tree *T,int e);
TreeNode *bst_remove_at(TreeNode *x);

int bst_update_height(TreeNode *x);
void bst_update_height_above(TreeNode *x);
#endif /* BST_h */
