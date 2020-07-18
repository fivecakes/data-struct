#include "bst.h"


int bst_update_height(struct tree_node *x)
{
    x->height = 1 + max(stature(x->left_child) , stature(x->right_child));
    //printf("updateheight %d,height=%d\n",x->data,x->height);
    return x->height;
}

void bst_update_height_above(struct tree_node *x)
{
    while (x != NULL) {
        bst_update_height(x);
        x = x->parent;
    }
}

static struct tree_node *bst_search_in(struct tree *T,struct tree_node *v, int e)
{
    if (!v) return v;
    if (v->data == e) return v;
    //记录刚刚访问过的节点，也就是返回值的父节点
    T->hot = v;
    
    if (e<v->data) {
        if (v->left_child) {
            return bst_search_in(T,v->left_child,e);
        }else{
            return NULL;
        }
    }else{
       if (v->right_child) {
            return bst_search_in(T,v->right_child,e);
        }else{
            return NULL;
        }
    }
}


struct tree_node *bst_search(struct tree *T,int e)
{
    return bst_search_in(T,T->top,e);
}



struct tree_node *bst_insert(struct tree *T,int e)
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
    new->color = WHITE;
    new->height = 0;
    
    if (!p) {
        T->top = new;
    }else{
        if (e<p->data) {
            p->left_child = new;
        }else{
            p->right_child = new;
        }
    }
    
    bst_update_height_above(new);
    
    T->size++;
    return new;
}


struct tree_node *bst_succ(struct tree_node *x)
{
    if (x->right_child != NULL) {
        x = x->right_child;
    }
    while (x->left_child != NULL) {
        x = x->left_child;
    }
    return x;
}

//删除x，返回被删除节点的代替者
struct tree_node *bst_remove_at(struct tree *T,struct tree_node *x)
{
    printf("删除节点%d\n",x->data);
    struct tree_node *p = x->parent;
    T->hot = p;
    
    if (!x->left_child){
        if (!p) {
            T->top = x->right_child;
            x->right_child->parent = NULL;
            return x->right_child;
        }else{
            if (p->left_child == x) {
                p->left_child = x->right_child;
            }else{
                p->right_child = x->right_child;
            }
            if (x->right_child) {
                x->right_child->parent = p;
            }
            return x->right_child;
        }
    }
    else if (!x->right_child){
        if (!p) {
            T->top = x->left_child;
            x->left_child->parent = NULL;
            return x->right_child;
        }else{
            if (p->left_child == x) {
                p->left_child = x->left_child;
            }else{
                p->right_child = x->left_child;
            }
            if (x->left_child) {
                x->left_child->parent = p;
            }
            return x->left_child;
        }
    }
    else{
        //交换x与x的直接后继w
        int tmp;
        struct tree_node *w = bst_succ(x);//x的直接后继
        T->hot = w->parent;
        //printf("%d的直接后继为%d\n",x->data,w->data);
        tmp = w->data;
        w->data = x->data;
        x->data = tmp;
        
        //删除w
        if (x->right_child == w) {
            w->parent->right_child = w->right_child;
        }else{
            w->parent->left_child = w->right_child;
        }

        if(w->right_child) w->right_child->parent = w->parent;
        return w->right_child;
    }
}

void bst_remove(struct tree *T,int e)
{
    struct tree_node *x = bst_search(T,e);
    if (!x) {
        printf("%d不存在，删除失败\n",e);
    }
    
    bst_remove_at(T,x);
    bst_update_height_above(T->hot);
    
    T->size--;
}


