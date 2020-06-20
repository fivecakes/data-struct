//
//  BST.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BST.h"


BinNode **searchIn(BinNode **v, int e,BinNode *hot)
{
    if (!*v || ((*v)->data == e)) return v;
    hot = *v;
    return searchIn(((e<(*v)->data?&(*v)->lChild:&(*v)->rChild)), e, hot);
}

BinNode **bst_search(BinTree *T,int e)
{
    BinNode *hot = NULL;
    return searchIn(&T->root,e,hot);
}





void bst_insert(BinTree *T,int e)
{
    BinNode **x = bst_search(T,e);
    if (!(*x)) {
        BinNode *new = malloc(sizeof(BinNode));
        new->parent = *x;
        new->lChild = NULL;
        new->rChild = NULL;
        new->data = e;
        new->height = 0;
        
        *x = new;
        
        updateHeightAbove(*x);
    }
    T->size++;
    
}


