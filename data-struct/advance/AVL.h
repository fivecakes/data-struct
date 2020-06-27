//
//  AVL.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef AVL_h
#define AVL_h
#include "commom.h"
#include "BST.h"

TreeNode *avl_insert(Tree *T,int e);
void avl_remove(Tree *T,int e);

#endif /* AVL_h */
