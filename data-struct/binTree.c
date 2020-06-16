//
//  binTree.c
//  data-struct
//
//  Created by book on 2020/6/15.
//  Copyright © 2020 book. All rights reserved.
//

#include "binTree.h"
#include "queue.h"

#define stature(p) ((p) ? (p)->height : -1)
#define max(a,b) ((a)>(b)?(a):(b))

struct BinNode{
    int data;
    struct BinNode *parent;
    struct BinNode *lChild;
    struct BinNode *rChild;
    int height;
    int npl;
    int color;
};

struct BinTree{
    int size;
    struct BinNode *root;
};

typedef struct BinNode BinNode;
typedef struct BinTree BinTree;

static int updateHeight(BinNode *x)
{
    return x->height = 1 + max(stature(x->lChild) , stature(x->rChild));
}

static void updateHeightAbove(BinNode *x)
{
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

static BinNode *insertAsRC(BinNode *x, int e)
{
    x->rChild = malloc(sizeof(BinNode));
    x->rChild->parent = x;
    updateHeightAbove(x);
    return x->rChild;
}

//层次遍历
static void travLevel(BinTree *T)
{
//    Queue Q = initQueue();
//    enqueue(&Q, T->root);
//    while (Q.size) {
//        BinNode *x = dequeue(&Q);
//        printf("%d",x->data);
//        enqueue(&Q, T->root);
//    }
}
