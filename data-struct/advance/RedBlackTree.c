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

void solveDoubleRed(TreeNode *x)
{
    printf("双红缺陷！\n");
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
        
    if (e<p->data) {
        p->lChild = new;
    }else{
        p->rChild = new;
    }
    redblack_update_height_above(new);
    
    T->size++;
    
    
    solveDoubleRed(new);
    
    return new;
}
