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

TreeNode *splay(TreeNode *v)
{
    if (!v) return NULL;
    
    TreeNode *p,*g;
    while ((p = v->parent) && (g = p->parent)) {
        if (g->rChild == p) {//
            if(p->rChild == v){ //zagzag
                p->parent = g->parent;
                return connectZagZag(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
            }else{//先右旋再左旋zigzag
                v->parent = g->parent;
                return connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
            }
        }else{
            if(p->rChild == v){//先左旋再右旋zagzig
                v->parent = g->parent;
                return connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
            }else{//zigzig
                p->parent = g->parent;
                return connectZigZig(g,p,v,v->lChild,v->rChild,p->rChild,g->rChild);
            }
        }
        
        if (!gg) {//若无曾祖父节点，则为树根
            <#statements#>
        }
    }

    
    return v;
}
