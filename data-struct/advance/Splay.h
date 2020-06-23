//
//  Splay.h
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef Splay_h
#define Splay_h
#include "BST.h"
#include <stdio.h>
TreeNode *splay_search(Tree *T,int e);
void splay_insert(Tree *T,int e);
void splay_remove(Tree *T,int e);
#endif /* Splay_h */
