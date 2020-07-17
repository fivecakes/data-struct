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
    a->rChild = T1; if(T1) T1->parent = a; bst_update_height(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; bst_update_height(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; bst_update_height(b);
    return b;
}


static TreeNode *connectZigZig(TreeNode *g,TreeNode *p,TreeNode *v,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    g->lChild = T2; if(T2) T2->parent = g;
    g->rChild = T3; if(T3) T3->parent = g; bst_update_height(g);
    p->lChild = T1; if(T1) T1->parent = p;
    p->rChild = g; g->parent = p; bst_update_height(p);
    v->lChild = T0; if(T0) T0->parent = v;
    v->rChild = p; p->parent = v; bst_update_height(v);
    return v;
}


static TreeNode *connectZagZag(TreeNode *g,TreeNode *p,TreeNode *v,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    g->lChild = T0; if(T0) T0->parent = g;
    g->rChild = T1; if(T1) T1->parent = g; bst_update_height(g);
    p->lChild = g; g->parent = p;
    p->rChild = T2; if(T2) T2->parent = p; bst_update_height(p);
    v->lChild = p; p->parent = v;
    v->rChild = T3; if(T3) T3->parent = v; bst_update_height(v);
    return v;
}

static TreeNode *Zig(TreeNode *v,TreeNode *r,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    r->lChild = Y; if(Y) Y->parent = r;
    r->rChild = Z; if(Z) Z->parent = r; bst_update_height(r);
    v->lChild = X; if(X) X->parent = v;
    v->rChild = r; r->parent = v; bst_update_height(v);
    return v;
}


static TreeNode *Zag(TreeNode *v,TreeNode *r,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    r->lChild = X; if(X) X->parent = r;
    r->rChild = Y; if(Y) Y->parent = r; bst_update_height(r);
    v->lChild = r; r->parent = v;
    v->rChild = Z; if(Z) Z->parent = v; bst_update_height(v);
    return v;
}

TreeNode *splay(Tree *T,TreeNode *v)
{
    //如果伸展根节点，直接返回
    if (!v->parent) {
        return v;
    }
    
    printf("伸展%d\n",v->data);
    
    TreeNode *p,*g,*gg;
    
    while ((p = v->parent) && (g = p->parent)) {
        gg = g->parent;
        
        if (g->rChild == p) {
            if(p->rChild == v){ //zagzag
                printf("zagzag\n");
                connectZagZag(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
            }else{//先右旋再左旋zigzag
                printf("zigzag\n");
                connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
            }
        }else{
            if(p->rChild == v){//先左旋再右旋zagzig
                printf("zagzig\n");
                connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
            }else{//zigzig
                printf("zigzig\n");
                connectZigZig(g,p,v,v->lChild,v->rChild,p->rChild,g->rChild);
            }
        }
 
        //将新子树接回原树
        if (gg) {
            if (gg->rChild == g) {
                gg->rChild = v;
                v->parent = gg;
            }else{
                gg->lChild = v;
                v->parent = gg;
            }
        }else{
            v->parent = NULL;
            T->top = v;
        }
    }

    //如果v的深度是奇数，最后一步，v只有父亲，没有祖父，所以需要额外一次旋转
    if (v->parent && !v->parent->parent) {
        if (v->parent->lChild == v) {
            printf("最后一步Zig\n");
            Zig(v, v->parent, v->lChild, v->rChild, v->parent->rChild);
        }else{
            printf("最后一步Zag\n");
            Zag(v, v->parent, v->parent->lChild, v->lChild, v->rChild);
        }
        v->parent = NULL;
        T->top = v;
    }//伸展完成,v到达树根
    
    
    return v;
}


TreeNode *splay_search(Tree *T,int e)
{
    printf("搜索%d\n",e);
    
    TreeNode *v = bst_search(T,e);
    TreeNode *p = T->hot;
    TreeNode *root;
    
    if (!v) {
        printf("未搜到%d\n",e);
    }
    
    //如果是空树，直接返回
    if (!p) return NULL;
    
    root = splay(T,v?v:p);
    //writeTreeToDotFile(*T,"a+","伸展后。");
    return root;
}


void splay_insert(Tree *T,int e)
{
    TreeNode *root = splay_search(T,e);
    
    TreeNode *new = malloc(sizeof(TreeNode));
    new->data = e;
    new->height = 0;
    new->color = WHITE;
    new->lChild = NULL;
    new->rChild = NULL;
    
    if (!root) {
        //空树则
        new->parent = NULL;
        T->top = new;
    }else{
        if (e<root->data) {
            printf("将%d插入到%d的左端\n",e,root->data);
            new->lChild = root->lChild;
            if (root->lChild)
                root->lChild->parent = new;
            new->parent = root;
            root->lChild = new;
        }else{
            printf("将%d插入到%d的右端\n",e,root->data);
            new->rChild = root->rChild;
            if (root->rChild)
                root->rChild->parent = new;
            new->parent = root;
            root->rChild = new;
        }
    }
    
    
    bst_update_height_above(new);
}


void splay_remove(Tree *T,int e)
{
    TreeNode *x = splay_search(T,e);
    if (!x || x->data != e) {
        return;
    }
    bst_remove_at(T,x);
    bst_update_height_above(T->hot);
    T->size--;
}
