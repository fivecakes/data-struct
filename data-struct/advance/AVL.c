//
//  AVL.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "AVL.h"

static int avl_balanced(BinNode *g)
{
    int bal_fac = stature(g->lChild) - stature(g->rChild);
    printf("%d点平衡因子为%d,左侧高度%d,右侧高度%d\n",
           g->data,bal_fac,
           stature(g->lChild) , stature(g->rChild));
    
    if (-2<bal_fac && bal_fac<2) {
        return 1;
    }else{
        return 0;
    }
}

static BinNode *connect34(BinNode *a,BinNode *b,BinNode *c,BinNode *T0,BinNode *T1,BinNode *T2,BinNode *T3)
{
    a->lChild = T0; if(T0) T0->parent = a;
    a->rChild = T1; if(T1) T1->parent = a; updateHeight(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; updateHeight(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; updateHeight(b);
    return b;
}

BinNode *avl_rotate_at(BinNode *v)
{
    BinNode *p = v->parent;
    BinNode *g = p->parent;
    
    if (stature(g->lChild) < stature(g->rChild)) {
        if(stature(p->lChild) < stature(p->rChild)){ //左旋zag
            p->parent = g->parent;
            return connect34(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
        }else{//先右旋再左旋zigzag
            v->parent = g->parent;
            return connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
        }
    }else{
        if(stature(p->lChild)<stature(p->rChild)){//先左旋再右旋zagzig
            v->parent = g->parent;
            return connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
        }else{//右旋zig
            printf("右旋\n");
            p->parent = g->parent;
            return connect34(v,p,g,v->lChild,v->rChild,p->rChild,g->rChild);
        }
    }
    
}

BinNode *tallerChild(BinNode *p)
{
    if (stature(p->lChild)<stature(p->rChild)) {
        return p->rChild;
    }else{
        return p->lChild;
    }
}

BinNode **getTallerChildAddress(BinNode *p)
{
    if (stature(p->lChild)<stature(p->rChild)) {
        return &p->rChild;
    }else{
        return &p->lChild;
    }
}

BinNode *avl_insert(BinTree *T,int e)
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
    
    T->size++;

    printf("新插入%d,向上检测平衡因子\n",e);
    //以下从从xp出发逐层向上，依次检测各代祖先
    for(BinNode *g = xp; (g && g->parent); g = g->parent){
        if(!avl_balanced(g)){
            printf("%d不平衡,开始调整\n",g->data);
            BinNode **ptc = getTallerChildAddress(g->parent);
            BinNode *b = avl_rotate_at(tallerChild(tallerChild(g)));
            *ptc = b;
            updateHeightAbove(b);
            break;
        }else{
            updateHeightAbove(g);
        }
    }
    
    return new;
}


void avl_delete(BinTree *T,int e)
{
    
}
