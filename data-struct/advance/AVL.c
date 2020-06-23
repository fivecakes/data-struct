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
    a->rChild = T1; if(T1) T1->parent = a; updateHeight(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; updateHeight(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; updateHeight(b);
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
    
    T->size++;

    printf("插入%d,\n",e);
    //以下从从xp出发逐层向上，依次检测各代祖先
    for(TreeNode *g = xp; (g && g->parent); g = g->parent){
        if(!avl_balanced(g)){
            printf("%d不平衡,开始调整\n",g->data);
            TreeNode *b = avl_rotate_at(tallerChild(tallerChild(g)));
            updateHeightAbove(b);
            break;
        }else{
            updateHeightAbove(g);
        }
    }
    
    return new;
}



void avl_remove(Tree *T,int e)
{
    TreeNode *x;
    TreeNode **ptc; //指向要被删除的孩子的指针的指针
    TreeNode *xp = bst_search_parent(T,e);
    //确定要删除左孩子还是右孩子
    if (e<xp->data) {
        ptc = &xp->lChild;
        x = xp->lChild;
    }else{
        ptc = &xp->rChild;
        x = xp->rChild;
    }
    
    bst_remove_at(ptc,xp,x);
    
    printf("删除%d,\n",e);
    //从xp出发逐层向上，依次检查各代祖先
    for (TreeNode *g = xp; g; g = g->parent) {
         if(!avl_balanced(g)){
             printf("%d不平衡,开始调整\n",g->data);
             avl_rotate_at(tallerChild(tallerChild(g)));
         }
        updateHeight(g);
    }
    
    T->size--;
}
