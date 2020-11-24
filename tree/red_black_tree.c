#include "red_black_tree.h"



int redblack_update_height(struct tree_node *x)
{
    x->height = max(stature(x->left_child) , stature(x->right_child));
    
    //只统计黑高度
    if (x->color == BLACK) {
        x->height++;
    }
    
    return x->height;
}

void redblack_update_height_above(struct tree_node *x)
{
    while (x != NULL) {
        redblack_update_height(x);
        x = x->parent;
    }
}


static struct tree_node *solveRR_1(struct tree_node *a,struct tree_node *b,struct tree_node *c,struct tree_node *T0,struct tree_node *T1,struct tree_node *T2,struct tree_node *T3)
{
    a->left_child = T0; if(T0) T0->parent = a;
    a->right_child = T1; if(T1) T1->parent = a; redblack_update_height(a);
    c->left_child = T2; if(T2) T2->parent = c;
    c->right_child = T3; if(T3) T3->parent = c; redblack_update_height(c);
    b->left_child = a; a->parent = b;
    b->right_child = c; c->parent = b; redblack_update_height(b);
    a->color = RED;c->color = RED;b->color = BLACK;
    return b;
}


static void solveRR_2(struct tree_node *x,struct tree_node *p,struct tree_node *g,struct tree_node *u)
{
    g->color = RED;
    p->color = BLACK;
    u->color = BLACK;
    redblack_update_height(g);
    redblack_update_height(p);
    redblack_update_height(u);
}

void solveDoubleRed(struct tree *T,struct tree_node *x)
{
    if (!x->parent || !x->parent->parent) return;
    if (x->parent->color != RED) return;
    
    struct tree_node *p = x->parent;
    struct tree_node *g = p->parent;
    struct tree_node *gg = g->parent;
    struct tree_node *b,*u;
    
    if (!g->left_child || !g->right_child || g->left_child->color == BLACK || g->right_child->color == BLACK) {
        printf("双红缺陷,叔父为黑或不存在\n");

        if (g->left_child == p && p->left_child == x) {
            b=solveRR_1(x,p,g,x->left_child,x->right_child,p->right_child,g->right_child);
        }else if (g->left_child == p && p->right_child == x){
            b=solveRR_1(p,x,g,p->left_child,x->left_child,x->right_child,g->right_child);
        }else if (g->right_child == p && p->right_child == x){
            b=solveRR_1(g,p,x,g->left_child,p->left_child,x->left_child,x->right_child);
        }else{
            b=solveRR_1(g,x,p,g->left_child,x->left_child,x->right_child,p->right_child);
        }
        //将新子树接回原树
        if (gg) {
            if (gg->right_child == g) {
                gg->right_child = b;
                b->parent = gg;
            }else{
                gg->left_child = b;
                b->parent = gg;
            }
        }else{
            b->parent = NULL;
            T->top = b;
        }
    }else{
        printf("双红缺陷,叔父为红\n");
        if (g->left_child == p) {
            u = g->right_child;
        }else{
            u = g->left_child;
        }
        solveRR_2(x,p,g,u);
        if (!gg) {
            g->color = BLACK;
        }
        solveDoubleRed(T,g);
    }
}

struct tree_node *redblack_insert(struct tree *T,int e)
{
    struct tree_node *x = bst_search(T,e);
    if (x) {
        printf("%d已存在，插入失败\n",e);
    }else{
        printf("插入%d\n",e);
    }
    struct tree_node *p = T->hot;
    
    struct tree_node *new = malloc(sizeof(struct tree_node));
    new->parent = p;
    new->left_child = NULL;
    new->right_child = NULL;
    new->data = e;
    new->color = RED;
    new->height = -1;
    
    if (p) {
        if (e<p->data) {
            p->left_child = new;
        }else{
            p->right_child = new;
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

struct tree_node * solveBB_1(struct tree_node *t,struct tree_node *s,struct tree_node *p,struct tree_node *T0,struct tree_node *T1,struct tree_node *T2,struct tree_node *T3)
{
    s->color = p->color;
    s->left_child = t; if(t) t->parent = s;
    s->right_child = p; if(p) p->parent = s;
    
    t->left_child = T0; if(T0) T0->parent = t;
    t->right_child = T1; if(T1) T1->parent = t; t->color = BLACK;
    p->left_child = T2; if(T2) T2->parent = p;
    p->right_child = T3; if(T3) T3->parent = p; p->color = BLACK;
    return s;
}



static struct tree_node * zig(struct tree_node *s,struct tree_node *p,struct tree_node *X,struct tree_node *Y,struct tree_node *Z)
{
    s->color = BLACK;
    p->color = RED;
    
    p->left_child = Y; if(Y) Y->parent = p;
    p->right_child = Z; if(Z) Z->parent = p;
    s->left_child = X; if(X) X->parent = s;
    s->right_child = p; p->parent = s;
    return s;
}

static struct tree_node * zag(struct tree_node *s,struct tree_node *p,struct tree_node *X,struct tree_node *Y,struct tree_node *Z)
{
    s->color = BLACK;
    p->color = RED;

    p->left_child = X; if(X) X->parent = p;
    p->right_child = Y; if(Y) Y->parent = p;
    s->left_child = p; p->parent = s;
    s->right_child = Z; if(Z) Z->parent = s;
    return s;
}

void solveDoubleBlack(struct tree *tree,struct tree_node *p,struct tree_node *r)
{
    write_tree_to_dotfile(tree,"a+","solveDoubleBlack");

    if (!p) {
        return;
    }
        
    struct tree_node *g = p->parent;
    struct tree_node *s,*t = NULL;
    struct tree_node *new;
    
    if (p->left_child == r) {
        s = p->right_child;
    }else{
        s = p->left_child;
    }
    
    if (s->left_child && s->left_child->color == RED) {
        t = s->left_child;
    }
    if (s->right_child && s->right_child->color == RED) {
        t = s->right_child;
    }
    
    if (s && s->color == RED) {
        //BB-3
        printf("BB-3\n");
        if (p->left_child == s) {
            new = zig(s,p,s->left_child,s->right_child,p->right_child);
        }else{
            new = zag(s,p,p->left_child,s->left_child,s->right_child);
        }
        
        //接回到原树
        if (g) {
            if (g->left_child == p) {
                g->left_child = new;
            }else{
                g->right_child = new;
            }
            new->parent = g;
        }else{
            new->parent = NULL;
            tree->top = new;
        }
        
        solveDoubleBlack(tree,p,r);
    }else{
        if (t) {
            //BB-1,与AVL树一样分四种情况，进行connect34
            printf("BB-1\n");
            printf("p,s,t = %d,%d,%d\n",p->data,s->data,t->data);
            if (p->left_child == s) {
                if (s->left_child == t) {
                    printf("case1\n");
                    new = solveBB_1(t,s,p,t->left_child,t->right_child,s->right_child,r);
                }else{
                    printf("case2\n");
                    new = solveBB_1(s,t,p,s->left_child,t->left_child,t->right_child,r);
                }
            }else{
                if (s->left_child == t) {
                    printf("case3\n");
                    new = solveBB_1(p,t,s,r,t->left_child,t->right_child,s->right_child);
                }else{
                    printf("case4\n");
                    new = solveBB_1(p,s,t,r,s->left_child,t->left_child,t->right_child);
                }
            }
            //接回到原树
            if (g) {
                if (g->left_child == p) {
                    g->left_child = new;
                }else{
                    g->right_child = new;
                }
                new->parent = g;
            }else{
                new->parent = NULL;
                tree->top = new;
            }
        }else{
            if (p->color == RED) {
                //BB-2R
                printf("BB-2R\n");
                p->color = BLACK;
                s->color = RED;
                if (p->left_child == s) {
                    p->right_child = r;
                }else{
                    p->left_child = r;
                }
            }else{
                //BB-2B
                printf("BB-2B\n");
                s->color = RED;
                if (p->left_child == s) {
                    p->right_child = r;
                }else{
                    p->left_child = r;
                }
            }
            solveDoubleBlack(tree,p,r);
        }
    }
}

void redblack_remove(struct tree *T,int e)
{
    struct tree_node *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    struct tree_node *r = bst_remove_at(T,x);
    
    //1.x仅有一个后代r
    //2.当x有两个后代时,会用后继w替换x的值,原x位置不会改变红黑树性质
    //所以问题转变为删除w,此时w仅有一个后代r
    
    if(!T->hot){
        printf("删除根节点\n");
        return;
    }
    
    //x为红，无需调整
    
    //r为红,仅需将r染成黑色
    if (r && r->color==RED) {
        r->color = BLACK;
        return;
    }
    
    //先放放，可以参考https://github.com/smartjinyu/DSA-djh/blob/master/BST/BST/RedBlack.h
    
    solveDoubleBlack(T,T->hot,r);
    
    
    redblack_update_height_above(T->hot);
    
    T->size--;
}


