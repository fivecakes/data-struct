#include "splay.h"

static struct tree_node *connect34(struct tree_node *a,struct tree_node *b,struct tree_node *c,struct tree_node *t0,struct tree_node *t1,struct tree_node *t2,struct tree_node *t3)
{
    a->left_child = t0; if(t0) t0->parent = a;
    a->right_child = t1; if(t1) t1->parent = a; bst_update_height(a);
    c->left_child = t2; if(t2) t2->parent = c;
    c->right_child = t3; if(t3) t3->parent = c; bst_update_height(c);
    b->left_child = a; a->parent = b;
    b->right_child = c; c->parent = b; bst_update_height(b);
    return b;
}


static struct tree_node *connectZigZig(struct tree_node *g,struct tree_node *p,struct tree_node *v,struct tree_node *t0,struct tree_node *t1,struct tree_node *t2,struct tree_node *t3)
{
    g->left_child = t2; if(t2) t2->parent = g;
    g->right_child = t3; if(t3) t3->parent = g; bst_update_height(g);
    p->left_child = t1; if(t1) t1->parent = p;
    p->right_child = g; g->parent = p; bst_update_height(p);
    v->left_child = t0; if(t0) t0->parent = v;
    v->right_child = p; p->parent = v; bst_update_height(v);
    return v;
}


static struct tree_node *connectZagZag(struct tree_node *g,struct tree_node *p,struct tree_node *v,struct tree_node *t0,struct tree_node *t1,struct tree_node *t2,struct tree_node *t3)
{
    g->left_child = t0; if(t0) t0->parent = g;
    g->right_child = t1; if(t1) t1->parent = g; bst_update_height(g);
    p->left_child = g; g->parent = p;
    p->right_child = t2; if(t2) t2->parent = p; bst_update_height(p);
    v->left_child = p; p->parent = v;
    v->right_child = t3; if(t3) t3->parent = v; bst_update_height(v);
    return v;
}

static struct tree_node *Zig(struct tree_node *v,struct tree_node *r,struct tree_node *x,struct tree_node *y,struct tree_node *z)
{
    r->left_child = y; if(y) y->parent = r;
    r->right_child = z; if(z) z->parent = r; bst_update_height(r);
    v->left_child = x; if(x) x->parent = v;
    v->right_child = r; r->parent = v; bst_update_height(v);
    return v;
}


static struct tree_node *Zag(struct tree_node *v,struct tree_node *r,struct tree_node *x,struct tree_node *y,struct tree_node *z)
{
    r->left_child = x; if(x) x->parent = r;
    r->right_child = y; if(y) y->parent = r; bst_update_height(r);
    v->left_child = r; r->parent = v;
    v->right_child = z; if(z) z->parent = v; bst_update_height(v);
    return v;
}

struct tree_node *splay(struct tree *t,struct tree_node *v)
{
    //如果伸展根节点，直接返回
    if (!v->parent) {
        return v;
    }
    
    printf("伸展%d\n",v->data);
    
    struct tree_node *p,*g,*gg;
    
    while ((p = v->parent) && (g = p->parent)) {
        gg = g->parent;
        
        if (g->right_child == p) {
            if(p->right_child == v){ //zagzag
                printf("zagzag\n");
                connectZagZag(g,p,v,g->left_child,p->left_child,v->left_child,v->right_child);
            }else{//先右旋再左旋zigzag
                printf("zigzag\n");
                connect34(g,v,p,g->left_child,v->left_child,v->right_child,p->right_child);
            }
        }else{
            if(p->right_child == v){//先左旋再右旋zagzig
                printf("zagzig\n");
                connect34(p,v,g,p->left_child,v->left_child,v->right_child,g->right_child);
            }else{//zigzig
                printf("zigzig\n");
                connectZigZig(g,p,v,v->left_child,v->right_child,p->right_child,g->right_child);
            }
        }
 
        //将新子树接回原树
        if (gg) {
            if (gg->right_child == g) {
                gg->right_child = v;
                v->parent = gg;
            }else{
                gg->left_child = v;
                v->parent = gg;
            }
        }else{
            v->parent = NULL;
            t->top = v;
        }
    }

    //如果v的深度是奇数，最后一步，v只有父亲，没有祖父，所以需要额外一次旋转
    if (v->parent && !v->parent->parent) {
        if (v->parent->left_child == v) {
            printf("最后一步Zig\n");
            Zig(v, v->parent, v->left_child, v->right_child, v->parent->right_child);
        }else{
            printf("最后一步Zag\n");
            Zag(v, v->parent, v->parent->left_child, v->left_child, v->right_child);
        }
        v->parent = NULL;
        t->top = v;
    }//伸展完成,v到达树根
    
    
    return v;
}


struct tree_node *splay_search(struct tree *t,int e)
{
    printf("搜索%d\n",e);
    
    struct tree_node *v = bst_search(t,e);
    struct tree_node *p = t->hot;
    struct tree_node *root;
    
    if (!v) {
        printf("未搜到%d\n",e);
    }
    
    //如果是空树，直接返回
    if (!p) return NULL;
    
    root = splay(t,v?v:p);
    //writeTreeToDotFile(*T,"a+","伸展后。");
    return root;
}


void splay_insert(struct tree *t,int e)
{
    struct tree_node *root = splay_search(t,e);
    
    struct tree_node *new = malloc(sizeof(struct tree_node));
    new->data = e;
    new->height = 0;
    new->color = WHITE;
    new->left_child = NULL;
    new->right_child = NULL;
    
    if (!root) {
        //空树则
        new->parent = NULL;
        t->top = new;
    }else{
        if (e<root->data) {
            printf("将%d插入到%d的左端\n",e,root->data);
            new->left_child = root->left_child;
            if (root->left_child)
                root->left_child->parent = new;
            new->parent = root;
            root->left_child = new;
        }else{
            printf("将%d插入到%d的右端\n",e,root->data);
            new->right_child = root->right_child;
            if (root->right_child)
                root->right_child->parent = new;
            new->parent = root;
            root->right_child = new;
        }
    }
    
    
    bst_update_height_above(new);
}


void splay_remove(struct tree *t,int e)
{
    struct tree_node *x = splay_search(t,e);
    if (!x || x->data != e) {
        return;
    }
    bst_remove_at(t,x);
    bst_update_height_above(t->hot);
    t->size--;
}
