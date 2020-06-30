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


static TreeNode *solveRR_1(TreeNode *a,TreeNode *b,TreeNode *c,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    a->lChild = T0; if(T0) T0->parent = a;
    a->rChild = T1; if(T1) T1->parent = a; redblack_update_height(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; redblack_update_height(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; redblack_update_height(b);
    a->color = RED;c->color = RED;b->color = BLACK;
    return b;
}


static void solveRR_2(TreeNode *x,TreeNode *p,TreeNode *g,TreeNode *u)
{
    g->color = RED;
    p->color = BLACK;
    u->color = BLACK;
    redblack_update_height(g);
    redblack_update_height(p);
    redblack_update_height(u);
}

void solveDoubleRed(Tree *T,TreeNode *x)
{
    if (!x->parent || !x->parent->parent) return;
    if (x->parent->color != RED) return;
    
    TreeNode *p = x->parent;
    TreeNode *g = p->parent;
    TreeNode *gg = g->parent;
    TreeNode *b,*u;
    
    if (!g->lChild || !g->rChild || g->lChild->color == BLACK || g->rChild->color == BLACK) {
        printf("双红缺陷,叔父为黑或不存在\n");

        if (g->lChild == p && p->lChild == x) {
            b=solveRR_1(x,p,g,x->lChild,x->rChild,p->rChild,g->rChild);
        }else if (g->lChild == p && p->rChild == x){
            b=solveRR_1(p,x,g,p->lChild,x->lChild,x->rChild,g->rChild);
        }else if (g->rChild == p && p->rChild == x){
            b=solveRR_1(g,p,x,g->lChild,p->lChild,x->lChild,x->rChild);
        }else{
            b=solveRR_1(g,x,p,g->lChild,x->lChild,x->rChild,p->rChild);
        }
        //将新子树接回原树
        if (gg) {
            if (gg->rChild == g) {
                gg->rChild = b;
                b->parent = gg;
            }else{
                gg->lChild = b;
                b->parent = gg;
            }
        }else{
            b->parent = NULL;
            T->top = b;
        }
    }else{
        printf("双红缺陷,叔父为红\n");
        if (g->lChild == p) {
            u = g->rChild;
        }else{
            u = g->lChild;
        }
        solveRR_2(x,p,g,u);
        if (!gg) {
            g->color = BLACK;
        }
        solveDoubleRed(T,g);
    }
}

TreeNode *redblack_insert(Tree *T,int e)
{
    TreeNode *x = bst_search(T,e);
    if (x) {
        printf("%d已存在，插入失败\n",e);
    }else{
        printf("插入%d\n",e);
    }
    TreeNode *p = T->hot;
    
    TreeNode *new = malloc(sizeof(TreeNode));
    new->parent = p;
    new->lChild = NULL;
    new->rChild = NULL;
    new->data = e;
    new->color = RED;
    new->height = -1;
    
    if (p) {
        if (e<p->data) {
            p->lChild = new;
        }else{
            p->rChild = new;
        }
        solveDoubleRed(T,new);
        redblack_update_height_above(new);
    }else{
        new->color = BLACK;
        T->top = new;
    }
    
    T->size++;
    
    return new;
}

TreeNode * solveBB_1(TreeNode *t,TreeNode *s,TreeNode *p,TreeNode *T0,TreeNode *T1,TreeNode *T2,TreeNode *T3)
{
    s->color = p->color;
    s->lChild = t; if(t) t->parent = s;
    s->rChild = p; if(p) p->parent = s;
    
    t->lChild = T0; if(T0) T0->parent = t;
    t->rChild = T1; if(T1) T1->parent = t; t->color = BLACK;
    p->lChild = T2; if(T2) T2->parent = p;
    p->rChild = T3; if(T3) T3->parent = p; p->color = BLACK;
    return s;
}



static TreeNode * zig(TreeNode *s,TreeNode *p,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    s->color = BLACK;
    p->color = RED;
    
    p->lChild = Y; if(Y) Y->parent = p;
    p->rChild = Z; if(Z) Z->parent = p;
    s->lChild = X; if(X) X->parent = s;
    s->rChild = p; p->parent = s;
    return s;
}

static TreeNode * zag(TreeNode *s,TreeNode *p,TreeNode *X,TreeNode *Y,TreeNode *Z)
{
    s->color = BLACK;
    p->color = RED;

    p->lChild = X; if(X) X->parent = p;
    p->rChild = Y; if(Y) Y->parent = p;
    s->lChild = p; p->parent = s;
    s->rChild = Z; if(Z) Z->parent = s;
    return s;
}

void solveDoubleBlack(Tree *T,TreeNode *p,TreeNode *r)
{
    writeTreeToDotFile(T,"a+","solveDoubleBlack");

    if (!p) {
        return;
    }
        
    TreeNode *g = p->parent;
    TreeNode *s,*t = NULL;
    TreeNode *new;
    
    if (p->lChild == r) {
        s = p->rChild;
    }else{
        s = p->lChild;
    }
    
    if (s->lChild && s->lChild->color == RED) {
        t = s->lChild;
    }
    if (s->rChild && s->rChild->color == RED) {
        t = s->rChild;
    }
    
    if (s && s->color == RED) {
        //BB-3
        printf("BB-3\n");
        if (p->lChild == s) {
            new = zig(s,p,s->lChild,s->rChild,p->rChild);
        }else{
            new = zag(s,p,p->lChild,s->lChild,s->rChild);
        }
        
        //接回到原树
        if (g) {
            if (g->lChild == p) {
                g->lChild = new;
            }else{
                g->rChild = new;
            }
            new->parent = g;
        }else{
            new->parent = NULL;
            T->top = new;
        }
        
        solveDoubleBlack(T,p,r);
    }else{
        if (t) {
            //BB-1,与AVL树一样分四种情况，进行connect34
            printf("BB-1\n");
            printf("p,s,t = %d,%d,%d\n",p->data,s->data,t->data);
            if (p->lChild == s) {
                if (s->lChild == t) {
                    printf("case1\n");
                    new = solveBB_1(t,s,p,t->lChild,t->rChild,s->rChild,r);
                }else{
                    printf("case2\n");
                    new = solveBB_1(s,t,p,s->lChild,t->lChild,t->rChild,r);
                }
            }else{
                if (s->lChild == t) {
                    printf("case3\n");
                    new = solveBB_1(p,t,s,r,t->lChild,t->rChild,s->rChild);
                }else{
                    printf("case4\n");
                    new = solveBB_1(p,s,t,r,s->lChild,t->lChild,t->rChild);
                }
            }
            //接回到原树
            if (g) {
                if (g->lChild == p) {
                    g->lChild = new;
                }else{
                    g->rChild = new;
                }
                new->parent = g;
            }else{
                new->parent = NULL;
                T->top = new;
            }
        }else{
            if (p->color == RED) {
                //BB-2R
                printf("BB-2R\n");
                p->color = BLACK;
                s->color = RED;
                if (p->lChild == s) {
                    p->rChild = r;
                }else{
                    p->lChild = r;
                }
            }else{
                //BB-2B
                printf("BB-2B\n");
                s->color = RED;
                if (p->lChild == s) {
                    p->rChild = r;
                }else{
                    p->lChild = r;
                }
            }
            solveDoubleBlack(T,p,r);
        }
    }
}

void redblack_remove(Tree *T,int e)
{
    TreeNode *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    TreeNode *r = bst_remove_at(T,x);
    
    //1.x仅有一个后代r
    //2.当x有两个后代时,会用后继w替换x的值,原x位置不会改变红黑树性质
    //所以问题转变为删除w,此时w仅有一个后代r
    
    //现在问题来了，如果r不存在，x还被删掉了，那么怎么知道x的颜色？
    //所以不应该直接调用bst_remove_at接口喽
    if ((r && r->color==RED) || x->color == RED) {
        if(r) r->color = BLACK;
    }else{
        solveDoubleBlack(T,T->hot,r);
    }
    
    
    redblack_update_height_above(T->hot);
    
    T->size--;
}


