//
//  Splay.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "Splay.h"

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


static TreeNode *connectZigZig(TreeNode *g,TreeNode *p,TreeNode *v,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    g->lChild = T2; if(T2) T2->parent = g;
    g->rChild = T3; if(T3) T3->parent = g; updateHeight(g);
    p->lChild = T1; if(T1) T1->parent = p;
    p->rChild = g; g->parent = p; updateHeight(p);
    v->lChild = T0; if(T1) T1->parent = v;
    v->rChild = p; p->parent = v; updateHeight(v);
    return v;
}


static TreeNode *connectZagZag(TreeNode *g,TreeNode *p,TreeNode *v,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    g->lChild = T0; if(T0) T0->parent = g;
    g->rChild = T1; if(T1) T1->parent = g; updateHeight(g);
    p->lChild = g; g->parent = p;
    p->rChild = T2; if(T2) T2->parent = p; updateHeight(p);
    v->lChild = p; p->parent = v;
    v->rChild = T3; if(T3) T3->parent = v; updateHeight(v);
    return v;
}

static TreeNode *Zig(TreeNode *v,TreeNode *r,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    r->lChild = Y; if(Y) Y->parent = r;
    r->rChild = Z; if(Z) Z->parent = r; updateHeight(r);
    v->lChild = X; if(Z) X->parent = v;
    v->rChild = r; r->parent = v; updateHeight(v);
    return v;
}


static TreeNode *Zag(TreeNode *v,TreeNode *r,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    r->lChild = X; if(X) X->parent = r;
    r->rChild = Y; if(Y) Y->parent = r; updateHeight(r);
    v->lChild = r; r->parent = v;
    v->rChild = Z; if(Z) Z->parent = v; updateHeight(v);
    return r;
}

TreeNode *splay(TreeNode *v)
{
    if (!v) return NULL;
    
    TreeNode *p,*g,*gg;
    while ((p = v->parent) && (g = p->parent) && (gg = g->parent)) {
        if (g->rChild == p) {//
            if(p->rChild == v){ //zagzag
                p->parent = g->parent;
                connectZagZag(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
            }else{//先右旋再左旋zigzag
                v->parent = g->parent;
                connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
            }
        }else{
            if(p->rChild == v){//先左旋再右旋zagzig
                v->parent = g->parent;
                connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
            }else{//zigzig
                p->parent = g->parent;
                connectZigZig(g,p,v,v->lChild,v->rChild,p->rChild,g->rChild);
            }
        }
        
        //将新子树接回原树;
        if (gg->rChild == g) {
            gg->rChild = v;
        }else{
            gg->lChild = v;
        }
    }
    
    //如果v的深度是奇数，最后一步，v只有父亲，没有祖父，所以需要额外一次旋转
    if (v->parent->parent) {
        if (v->parent->lChild == v) {
            v->parent->parent->lChild = Zig(v, v->parent, v->lChild, v->rChild, v->parent->rChild);
        }else{
            v->parent->parent->lChild = Zig(v, v->parent, v->parent->lChild, v->lChild, v->rChild);
        }
    }//伸展完成，v到达树根

    
    return v;
}


TreeNode *splay_search(Tree *T,int e)
{
    TreeNode *v;
    TreeNode *p = bst_search_parent(T,e);
    if (e<p->data) {
        v = p->lChild;
    }else{
        v = p->rChild;
    }
    
    TreeNode *root = splay(v?v:p);
    
    return root;
}


void splay_insert(Tree *T,int e)
{
    TreeNode *root = splay_search(T,e);
    
    TreeNode *new = malloc(sizeof(TreeNode));
    new->data = e;
    new->height = 0;
    new->parent = root;
    new->rChild = NULL;
    new->lChild = root->lChild;
    root->lChild = new;
    
    updateHeightAbove(new);
}


void splay_remove(Tree *T,int e)
{
    TreeNode *x = splay_search(T,e);
    if (!x || x->data != e) {
        return;
    }
    
    //交换x与x的直接后继w
    int tmp;
    TreeNode *w = bst_succ(x);//x的直接后继
    //printf("%d的直接后继为%d\n",x->data,w->data);
    tmp = w->data;
    w->data = x->data;
    x->data = tmp;
    //删除w
    w->parent->lChild = w->rChild;
    if(w->rChild) w->rChild->parent = w->parent;
}
