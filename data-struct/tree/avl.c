#include "avl.h"

static int avl_balanced(struct tree_node *g)
{
    int bal_fac = stature(g->left_child) - stature(g->right_child);
    //printf("%d点平衡因子为%d,左侧高度%d,右侧高度%d\n",g->data,bal_fac,stature(g->lChild) , stature(g->rChild));
    
    if (-2<bal_fac && bal_fac<2) {
        return 1;
    }else{
        return 0;
    }
}

static struct tree_node *connect34(struct tree_node *a,struct tree_node *b,struct tree_node *c,struct tree_node *T0,struct tree_node *T1,struct tree_node *T2,struct tree_node *T3)
{
    a->left_child = T0; if(T0) T0->parent = a;
    a->right_child = T1; if(T1) T1->parent = a; bst_update_height(a);
    c->left_child = T2; if(T2) T2->parent = c;
    c->right_child = T3; if(T3) T3->parent = c; bst_update_height(c);
    b->left_child = a; a->parent = b;
    b->right_child = c; c->parent = b; bst_update_height(b);
    return b;
}

struct tree_node *avl_rotate_at(struct tree *T,struct tree_node *v)
{
    struct tree_node *p = v->parent;
    struct tree_node *g = p->parent;
    struct tree_node *gg = g->parent;
    struct tree_node *b;
    
    if (g->right_child == p) {
        if(p->right_child == v){ //左旋zag
            b =  connect34(g,p,v,g->left_child,p->left_child,v->left_child,v->right_child);
        }else{//先右旋再左旋zigzag
            b =  connect34(g,v,p,g->left_child,v->left_child,v->right_child,p->right_child);
        }
    }else{
        if(p->right_child == v){//先左旋再右旋zagzig
            b =  connect34(p,v,g,p->left_child,v->left_child,v->right_child,g->right_child);
        }else{//右旋zig
            b =  connect34(v,p,g,v->left_child,v->right_child,p->right_child,g->right_child);
        }
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
    
    return b;
}

struct tree_node *tallerChild(struct tree_node *p)
{
    if (stature(p->left_child)<stature(p->right_child)) {
        return p->right_child;
    }else{
        return p->left_child;
    }
}


struct tree_node *avl_insert(struct tree *T,int e)
{
    struct tree_node *x = bst_search(T,e);
    if (x) {
        printf("%d已存在，插入失败\n",e);
    }
    struct tree_node *p = T->hot;
    
    struct tree_node *new = malloc(sizeof(struct tree_node));
    new->parent = p;
    new->left_child = NULL;
    new->right_child = NULL;
    new->data = e;
    new->height = 0;
    new->color = WHITE;
        
    if (!p) {
        T->top = new;
    }else{
        if (e<p->data) {
            p->left_child = new;
        }else{
            p->right_child = new;
        }
    }
    
    T->size++;

    printf("插入%d,\n",e);
    //以下从从xp出发逐层向上，依次检测各代祖先
    for(struct tree_node *g = p; g; g = g->parent){
        if(!avl_balanced(g)){
            printf("%d不平衡,开始调整\n",g->data);
            struct tree_node *b = avl_rotate_at(T,tallerChild(tallerChild(g)));
            bst_update_height_above(b);
            break;
        }else{
            bst_update_height_above(g);
        }
    }
    
    return new;
}



void avl_remove(struct tree *T,int e)
{
    struct tree_node *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    bst_remove_at(T,x);
    
    printf("删除%d,\n",e);
    //从p出发逐层向上，依次检查各代祖先
    for (struct tree_node *g = T->hot; g; g = g->parent) {
         if(!avl_balanced(g)){
             printf("%d不平衡,开始调整\n",g->data);
             avl_rotate_at(T,tallerChild(tallerChild(g)));
         }
        bst_update_height(g);
    }
    
    T->size--;
}
