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
    if ((*v == NULL) || ((*v)->data == e)) return v;
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

/**
 1.我需要返回指针的指针
 2.在局部函数取址返回的是局部变量的地址
 3.
 */
BinNode **bst_succ(BinNode **x)
{
    x = &((*x)->rChild);
    
    printf("ppppppppppp%p",(*x));
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
    else if ((*x)->lChild == NULL){
        *x = (*x)->lChild;
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        BinNode **w = bst_succ(x);//x的直接后继
        tmp = (*x)->data;
        (*w)->data = (*x)->data;
        (*x)->data = tmp;

        //删除
        *w = (*w)->rChild;
    }
    
}

void bst_delete(BinTree *T,int e)
{
    BinNode **x = bst_search(T,e);
    if (!(*x)) return;
    remove_at(x);
        
    updateHeightAbove(*x);
    
    T->size--;
}


