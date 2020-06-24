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
        if (v->lChild) {
            return bst_search_in(v->lChild,e);
        }else{
            return v;
        }
    }else{
       if (v->rChild) {
            return bst_search_in(v->rChild,e);
        }else{
            return v;
        }
    }
}

TreeNode *bst_search_parent(Tree *T,int e)
{
    return bst_search_in(T->top,e);
}






TreeNode *bst_insert(Tree *T,int e)
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

void bst_remove_at(TreeNode *x)
{
    TreeNode *p = x->parent;
    if (!x->lChild){
        if (p->lChild == x) {
            p->lChild = x->rChild;
        }else{
            p->rChild = x->rChild;
        }
        if (x->rChild) {
            x->rChild->parent = p;
        }
    }
    else if (!x->rChild){
        if (p->lChild == x) {
            p->lChild = x->rChild;
        }else{
            p->rChild = x->rChild;
        }
        if (x->lChild) {
            x->lChild->parent = p;
        }
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
        if (x->rChild == w) {
            w->parent->rChild = w->rChild;
            if(w->rChild) w->rChild->parent = w->parent;
        }else{
            w->parent->lChild = w->rChild;
            if(w->rChild) w->rChild->parent = w->parent;
        }
    }
}

void bst_remove(Tree *T,int e)
{
    TreeNode *x;
    TreeNode *p = bst_search_parent(T,e);
    printf("%d的父亲为%d\n",e,p->data);
    //确定要删除左孩子还是右孩子
    if (e<p->data) {
        x = p->lChild;
    }else{
        x = p->rChild;
    }
    
    printf("要删除的节点为%d\n",x->data);
    bst_remove_at(x);
        
    updateHeightAbove(x);
    
    T->size--;
}


