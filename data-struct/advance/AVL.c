//
//  AVL.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "AVL.h"

static int avl_balanced(TreeNode *g)
{
    if(g->parent == NULL){
        return 1;
    }
    int bal_fac = stature(g->lChild) - stature(g->rChild);
    //printf("%d点平衡因子为%d,左侧高度%d,右侧高度%d\n",g->data,bal_fac,stature(g->lChild) , stature(g->rChild));
    
    if (-2<bal_fac && bal_fac<2) {
        return 1;
    }else{
        return 0;
    }
}

static TreeNode *connect34(TreeNode *a,TreeNode *b,TreeNode *c,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    a->lChild = T0; if(T0) T0->parent = a;
    a->rChild = T1; if(T1) T1->parent = a; bst_update_height(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; bst_update_height(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; bst_update_height(b);
    return b;
}

TreeNode *avl_rotate_at(TreeNode *v)
{
    TreeNode *p = v->parent;
    TreeNode *g = p->parent;
    TreeNode *gg = g->parent;
    TreeNode *b;
    
    if (g->rChild == p) {
        if(p->rChild == v){ //左旋zag
            p->parent = g->parent;
            b =  connect34(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
        }else{//先右旋再左旋zigzag
            v->parent = g->parent;
            b =  connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
        }
    }else{
        if(p->rChild == v){//先左旋再右旋zagzig
            v->parent = g->parent;
            b =  connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
        }else{//右旋zig
            p->parent = g->parent;
            b =  connect34(v,p,g,v->lChild,v->rChild,p->rChild,g->rChild);
        }
    }
    
    //将新子树接回原树
    if (gg->rChild == g) {
        gg->rChild = b;
    }else{
        gg->lChild = b;
    }
    return b;
}

TreeNode *tallerChild(TreeNode *p)
{
    if (stature(p->lChild)<stature(p->rChild)) {
        return p->rChild;
    }else{
        return p->lChild;
    }
}

TreeNode **getTallerChildAddress(TreeNode *p,TreeNode *v)
{
    if (p->rChild == v) {
        return &p->rChild;
    }else{
        return &p->lChild;
    }
}

TreeNode *avl_insert(Tree *T,int e)
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
    new->height = 0;
        
    if (e<p->data) {
        p->lChild = new;
    }else{
        p->rChild = new;
    }
    
    T->size++;

    printf("插入%d,\n",e);
    //以下从从xp出发逐层向上，依次检测各代祖先
    for(TreeNode *g = p; (g && g->parent); g = g->parent){
        if(!avl_balanced(g)){
            printf("%d不平衡,开始调整\n",g->data);
            TreeNode *b = avl_rotate_at(tallerChild(tallerChild(g)));
            bst_update_height_above(b);
            break;
        }else{
            bst_update_height_above(g);
        }
    }
    
    return new;
}



void avl_remove(Tree *T,int e)
{
    TreeNode *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    TreeNode *p = bst_remove_at(x);
    
    printf("删除%d,\n",e);
    //从p出发逐层向上，依次检查各代祖先
    for (TreeNode *g = p; g; g = g->parent) {
         if(!avl_balanced(g)){
             printf("%d不平衡,开始调整\n",g->data);
             avl_rotate_at(tallerChild(tallerChild(g)));
         }
        bst_update_height(g);
    }
    
    T->size--;
}
