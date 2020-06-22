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
//    printf("%d点平衡因子为%d,左侧高度%d,右侧高度%d\n",
//           g->data,bal_fac,
//           stature(g->lChild) , stature(g->rChild));
    
    if (-2<bal_fac && bal_fac<2) {
        return 1;
    }else{
        return 0;
    }
}

//zag
BinNode* LeftRotate(BinNode* g){
    BinNode* temp=g->rChild;
    
    g->rChild=temp->lChild;
    if (temp->lChild)
        temp->lChild->parent = g;
    
    temp->lChild=g;
    g->parent = temp;
    
    return temp;
}

//zig
BinNode* RightRotate(BinNode* g){
    BinNode* temp=g->lChild;
    g->lChild=temp->rChild;
    if (temp->rChild)
        temp->rChild->parent =g;
    temp->rChild=g;
    g->parent =temp;
    return temp;
}

//zag-zig
BinNode* LeftRightRotate(BinNode* g){
    g->lChild=LeftRotate(g->lChild);
    if (g->lChild)
        g->lChild->parent = g;
    return RightRotate(g);
}

//zig-zag
BinNode* RightLeftRotate(BinNode* g){
    g->rChild=RightRotate(g->rChild);
    if (g->rChild)
        g->rChild->parent = g;
    return LeftRotate(g);
}


static void avl_rotate1(BinNode *g)
{
    
    BinNode *gp = g->parent;
    if (!gp) {
        printf("gp is null,g is %d\n",g->data);
        exit(0);
    }
    
    //zag左旋
    if (stature(g->lChild) < stature(g->rChild) && stature(g->rChild->lChild) < stature(g->rChild->rChild)) {
        if (stature(gp->lChild) < stature(gp->rChild)) {
            gp->rChild = LeftRotate(g);
            if (gp->rChild)
                gp->rChild->parent = gp;
            updateHeight(gp->rChild->lChild);
            updateHeight(gp->rChild->rChild);
            updateHeightAbove(gp->rChild);
        }else{
            gp->lChild = LeftRotate(g);
            if (gp->lChild)
                gp->lChild->parent = gp;
            updateHeight(gp->lChild->lChild);
            updateHeight(gp->lChild->rChild);
            updateHeightAbove(gp->lChild);
        }
    }
    //zig右旋
    if (stature(g->lChild) > stature(g->rChild) && stature(g->lChild->lChild) > stature(g->lChild->rChild)) {
        if (stature(gp->lChild) < stature(gp->rChild)) {
            gp->rChild = RightRotate(g);
            if (gp->rChild)
                gp->rChild->parent = gp;
            updateHeight(gp->rChild->lChild);
            updateHeight(gp->rChild->rChild);
            updateHeightAbove(gp->rChild);
        }else{
            gp->lChild = RightRotate(g);
            if (gp->lChild)
                gp->lChild->parent = gp;
            updateHeight(gp->lChild->lChild);
            updateHeight(gp->lChild->rChild);
            updateHeightAbove(gp->lChild);
        }
    }
    //zig-zag 先右旋再左旋
    if (stature(g->lChild) < stature(g->rChild) && stature(g->rChild->lChild) > stature(g->rChild->rChild)) {
        if (stature(gp->lChild) < stature(gp->rChild)) {
            gp->rChild = RightLeftRotate(g);
            if (gp->rChild)
                gp->rChild->parent = gp;
            updateHeight(gp->rChild->lChild);
            updateHeight(gp->rChild->rChild);
            updateHeightAbove(gp->rChild);
        }else{
            gp->lChild = RightLeftRotate(g);
            if (gp->lChild)
                gp->lChild->parent = gp;
            updateHeight(gp->lChild->lChild);
            updateHeight(gp->lChild->rChild);
            updateHeightAbove(gp->lChild);
        }
    }
    //zag-zig 先左旋再右旋
    if (stature(g->lChild) > stature(g->rChild) && stature(g->lChild->lChild) < stature(g->lChild->rChild)) {
        if (stature(gp->lChild) < stature(gp->rChild)) {
            gp->rChild = LeftRightRotate(g);
            if (gp->rChild)
                gp->rChild->parent = gp;
            updateHeight(gp->rChild->lChild);
            updateHeight(gp->rChild->rChild);
            updateHeightAbove(gp->rChild);
        }else{
            gp->lChild = LeftRightRotate(g);
            if (gp->lChild)
                gp->lChild->parent = gp;
            updateHeight(gp->lChild->lChild);
            updateHeight(gp->lChild->rChild);
            updateHeightAbove(gp->lChild);
        }
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
            avl_rotate(g);
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
