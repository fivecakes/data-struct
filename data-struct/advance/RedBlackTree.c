//
//  RedBlackTree.c
//  data-struct
//
//  Created by book on 2020/6/28.
//  Copyright © 2020 book. All rights reserved.
//

#include "RedBlackTree.h"



int redblack_update_height(TreeNode *x)
{
    x->height = max(stature(x->lChild) , stature(x->rChild));
    
    //只统计黑高度
    if (x->color == BLACK) {
        x->height++;
    }
    
    return x->height;
}

void redblack_update_height_above(TreeNode *x)
{
    while (x != NULL) {
        redblack_update_height(x);
        x = x->parent;
    }
}


static TreeNode *solveRR_1(TreeNode *a,TreeNode *b,TreeNode *c,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    a->lChild = T0; if(T0) T0->parent = a;
    a->rChild = T1; if(T1) T1->parent = a; redblack_update_height(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; redblack_update_height(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; redblack_update_height(b);
    a->color = RED;c->color = RED;b->color = BLACK;
    return b;
}


static void solveRR_2(TreeNode *x,TreeNode *p,TreeNode *g,TreeNode *u)
{
    g->color = RED;
    p->color = BLACK;
    u->color = BLACK;
    redblack_update_height(g);
    redblack_update_height(p);
    redblack_update_height(u);
}

void solveDoubleRed(Tree *T,TreeNode *x)
{
    if (!x->parent || !x->parent->parent) return;
    if (x->parent->color != RED) return;
    
    TreeNode *p = x->parent;
    TreeNode *g = p->parent;
    TreeNode *gg = g->parent;
    TreeNode *b,*u;
    
    if (!g->lChild || !g->rChild || g->lChild->color == BLACK || g->rChild->color == BLACK) {
        printf("双红缺陷,叔父为黑或不存在\n");

        if (g->lChild == p && p->lChild == x) {
            b=solveRR_1(x,p,g,x->lChild,x->rChild,p->rChild,g->rChild);
        }else if (g->lChild == p && p->rChild == x){
            b=solveRR_1(p,x,g,p->lChild,x->lChild,x->rChild,g->rChild);
        }else if (g->rChild == p && p->rChild == x){
            b=solveRR_1(g,p,x,g->lChild,p->lChild,x->lChild,x->rChild);
        }else{
            b=solveRR_1(g,x,p,g->lChild,x->lChild,x->rChild,p->rChild);
        }
        //将新子树接回原树
        if (gg) {
            if (gg->rChild == g) {
                gg->rChild = b;
                b->parent = gg;
            }else{
                gg->lChild = b;
                b->parent = gg;
            }
        }else{
            b->parent = NULL;
            T->top = b;
        }
    }else{
        printf("双红缺陷,叔父为红\n");
        if (g->lChild == p) {
            u = g->rChild;
        }else{
            u = g->lChild;
        }
        solveRR_2(x,p,g,u);
        if (!gg) {
            g->color = BLACK;
        }
    }
}

TreeNode *redblack_insert(Tree *T,int e)
{
    TreeNode *x = bst_search(T,e);
    if (x) {
        printf("%d已存在，插入失败\n",e);
    }
    TreeNode *p = T->hot;
    
    TreeNode *new = malloc(sizeof(TreeNode));
    new->parent = p;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->color = RED;
    new->height = -1;
    
    if (p) {
        if (e<p->data) {
            p->lChild = new;
        }else{
            p->rChild = new;
        }
        solveDoubleRed(T,new);
        redblack_update_height_above(new);
    }else{
        new->color = BLACK;
        T->top = new;
    }
    
    T->size++;
    
    return new;
}
