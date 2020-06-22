//
//  BST.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BST.h"


static BinNode *bst_search_in(BinNode *v, int e)
{
    if (v->data == e) return v->parent;
    if (e<v->data) {
        if (v->lChild != NULL) {
            return bst_search_in(v->lChild,e);
        }else{
            return v;
        }
    }else{
       if (v->rChild != NULL) {
            return bst_search_in(v->rChild,e);
        }else{
            return v;
        }
    }
}

BinNode *bst_search_parent(BinTree *T,int e)
{
    return bst_search_in(T->root,e);
}






BinNode *bst_insert(BinTree *T,int e)
{
    BinNode *xp = bst_search_parent(T,e);
    
    BinNode *new = malloc(sizeof(BinNode));
    new->parent = xp;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->height = 0;
        
    if (e<xp->data) {
        xp->lChild = new;
    }else{
        xp->rChild = new;
    }
    updateHeightAbove(new);
    
    T->size++;
    return new;
}


BinNode *bst_succ(BinNode *x)
{
    while (x->lChild != NULL) {
        x = x->lChild;
    }
    return x;
}



void bst_delete(BinTree *T,int e)
{
    BinNode *x;
    BinNode *xp = bst_search_parent(T,e);
    if (e<xp->data) {
        x = xp->lChild;
    }else{
        x = xp->rChild;
    }
    
    if (x->lChild == NULL){
        if (e<xp->data) {
            xp->lChild = x->rChild;
        }else{
            xp->rChild = x->rChild;
        }
    }
    else if (x->rChild == NULL){
        if (e<xp->data) {
            xp->lChild = x->lChild;
        }else{
            xp->rChild = x->lChild;
        }
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        BinNode *w = bst_succ(x);//x的直接后继
        tmp = w->data;
        w->data = x->data;
        x->data = tmp;
        
        //删除w
        w->parent->lChild = w->rChild;
    }
        
    updateHeightAbove(x);
    
    T->size--;
}


