//
//  BST.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BST.h"


BinNode **searchIn(BinNode **v, int e,BinNode **hot)
{
    if ((*v == NULL) || ((*v)->data == e)) return v;
    *hot = *v; //父亲的地址给hot
    return searchIn(((e<(*v)->data?&(*v)->lChild:&(*v)->rChild)), e, hot);
}

BinNode **bst_search(BinTree *T,int e,BinNode ** xp)
{
    return searchIn(&T->root,e,xp);
}






BinNode * bst_insert(BinTree *T,int e)
{
    BinNode **xp = malloc(sizeof(BinNode **));
    BinNode **x = bst_search(T,e,xp);
    
    if (!(*x)) {
        BinNode *new = malloc(sizeof(BinNode));
        new->parent = *xp;
        new->lChild = NULL;
        new->rChild = NULL;
        new->data = e;
        new->height = 0;
        
        //指向null的指针，这个null是新节点的位置
        *x = new;
        updateHeightAbove(new);
    }
    T->size++;
    return *x;
}

/**
 1.我需要返回指针的指针
 2.在局部函数取址返回的是局部变量的地址
 3.
 */
BinNode **bst_succ(BinNode **x)
{
    x = &((*x)->rChild);
    
    while ((*x)->lChild != NULL) {
        x = &((*x)->lChild);
    }
    return x;
}


void remove_at(BinNode **x)
{
    if ((*x)->lChild == NULL){
        *x = (*x)->rChild;
    }
    else if ((*x)->rChild == NULL){
        *x = (*x)->lChild;
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        BinNode **w = bst_succ(x);//x的直接后继
        //printf("%d直接后继为%d\n",(*x)->data,(*w)->data);
        tmp = (*w)->data;
        (*w)->data = (*x)->data;
        (*x)->data = tmp;
        
        //printf("%d直接后继为%d\n",(*x)->data,(*w)->data);
        //删除
        *w = (*w)->rChild;
    }
    
}

void bst_delete(BinTree *T,int e)
{
    //先找到那个要删除的节点
    BinNode **xp = malloc(sizeof(BinNode **));
    BinNode **x = bst_search(T,e,xp);
    if (!(*x)) return;
    //删除这个节点
    remove_at(x);
        
    updateHeightAbove(*x);
    
    T->size--;
}


