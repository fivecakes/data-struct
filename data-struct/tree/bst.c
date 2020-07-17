//
//  BST.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "bst.h"


int bst_update_height(TreeNode *x)
{
    x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
    //printf("updateheight %d,height=%d\n",x->data,x->height);
    return x->height;
}

void bst_update_height_above(TreeNode *x)
{
    while (x != NULL) {
        bst_update_height(x);
        x = x->parent;
    }
}

static TreeNode *bst_search_in(Tree *T,TreeNode *v, int e)
{
    if (!v) return v;
    if (v->data == e) return v;
    //记录刚刚访问过的节点，也就是返回值的父节点
    T->hot = v;
    
    if (e<v->data) {
        if (v->lChild) {
            return bst_search_in(T,v->lChild,e);
        }else{
            return NULL;
        }
    }else{
       if (v->rChild) {
            return bst_search_in(T,v->rChild,e);
        }else{
            return NULL;
        }
    }
}


TreeNode *bst_search(Tree *T,int e)
{
    return bst_search_in(T,T->top,e);
}



TreeNode *bst_insert(Tree *T,int e)
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
    new->color = WHITE;
    new->height = 0;
    
    if (!p) {
        T->top = new;
    }else{
        if (e<p->data) {
            p->lChild = new;
        }else{
            p->rChild = new;
        }
    }
    
    bst_update_height_above(new);
    
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

//删除x，返回被删除节点的代替者
TreeNode *bst_remove_at(Tree *T,TreeNode *x)
{
    printf("删除节点%d\n",x->data);
    TreeNode *p = x->parent;
    T->hot = p;
    
    if (!x->lChild){
        if (!p) {
            T->top = x->rChild;
            x->rChild->parent = NULL;
            return x->rChild;
        }else{
            if (p->lChild == x) {
                p->lChild = x->rChild;
            }else{
                p->rChild = x->rChild;
            }
            if (x->rChild) {
                x->rChild->parent = p;
            }
            return x->rChild;
        }
    }
    else if (!x->rChild){
        if (!p) {
            T->top = x->lChild;
            x->lChild->parent = NULL;
            return x->rChild;
        }else{
            if (p->lChild == x) {
                p->lChild = x->lChild;
            }else{
                p->rChild = x->lChild;
            }
            if (x->lChild) {
                x->lChild->parent = p;
            }
            return x->lChild;
        }
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        TreeNode *w = bst_succ(x);//x的直接后继
        T->hot = w->parent;
        //printf("%d的直接后继为%d\n",x->data,w->data);
        tmp = w->data;
        w->data = x->data;
        x->data = tmp;
        
        //删除w
        if (x->rChild == w) {
            w->parent->rChild = w->rChild;
        }else{
            w->parent->lChild = w->rChild;
        }

        if(w->rChild) w->rChild->parent = w->parent;
        return w->rChild;
    }
}

void bst_remove(Tree *T,int e)
{
    TreeNode *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    bst_remove_at(T,x);
    bst_update_height_above(T->hot);
    
    T->size--;
}

