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

void bst_remove_at(BinNode **ptc,BinNode *xp,BinNode *x)
{
    if (x->lChild == NULL){
        *ptc = x->rChild;
    }
    else if (x->rChild == NULL){
        *ptc = x->lChild;
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
}

void bst_remove(BinTree *T,int e)
{
    BinNode *x;
    BinNode **ptc; //指向要被删除的孩子的指针的指针
    BinNode *xp = bst_search_parent(T,e);
    //确定要删除左孩子还是右孩子
    if (e<xp->data) {
        ptc = &xp->lChild;
        x = xp->lChild;
    }else{
        ptc = &xp->rChild;
        x = xp->rChild;
    }
    bst_remove_at(ptc,xp,x);
        
    updateHeightAbove(x);
    
    T->size--;
}


