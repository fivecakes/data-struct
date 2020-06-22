//
//  AVL.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include "BST.h"

BinNode *avl_insert(BinTree *T,int e);
void avl_delete(BinTree *T,int e);

#endif /* AVL_h */
