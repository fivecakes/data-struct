//
//  BST.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BST.h"


static TreeNode *bst_search_in(TreeNode *v, int e)
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

TreeNode *bst_search_parent(BinTree *T,int e)
{
    return bst_search_in(T->root,e);
}






TreeNode *bst_insert(BinTree *T,int e)
{
    TreeNode *xp = bst_search_parent(T,e);
    
    TreeNode *new = malloc(sizeof(TreeNode));
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


TreeNode *bst_succ(TreeNode *x)
{
    if (x->rChild != NULL) {
        x = x->rChild;
    }
    while (x->lChild != NULL) {
        x = x->lChild;
    }
    return x;
}

void bst_remove_at(TreeNode **ptc,TreeNode *xp,TreeNode *x)
{
    if (x->lChild == NULL){
        *ptc = x->rChild;
        x->rChild->parent = xp;
    }
    else if (x->rChild == NULL){
        *ptc = x->lChild;
        x->lChild->parent = xp;
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        TreeNode *w = bst_succ(x);//x的直接后继
        //printf("%d的直接后继为%d\n",x->data,w->data);
        tmp = w->data;
        w->data = x->data;
        x->data = tmp;
        //删除w
        w->parent->lChild = w->rChild;
        w->rChild->parent = w->parent;
    }
}

void bst_remove(BinTree *T,int e)
{
    TreeNode *x;
    TreeNode **ptc; //指向要被删除的孩子的指针的指针
    TreeNode *p = bst_search_parent(T,e);
    //printf("%d的父亲为%d\n",e,p->data);
    //确定要删除左孩子还是右孩子
    if (e<p->data) {
        ptc = &p->lChild;
        x = p->lChild;
    }else{
        ptc = &p->rChild;
        x = p->rChild;
    }
    
    //printf("要删除的节点为%d\n",x->data);
    bst_remove_at(ptc,p,x);
        
    updateHeightAbove(x);
    
    T->size--;
}


