#ifndef binTree_h
#define binTree_h

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <limits.h>

#define NULL ((void*)0)


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
    struct BinNode *header; //哨兵节点
};

typedef struct BinNode BinNode;
typedef struct BinTree BinTree;

BinNode *insertAsRC(BinNode *x, int e);
BinNode *insertAsLC(BinNode *x, int e);
BinTree initBinTree(int e);
void travLevel(BinTree T,void visit(BinNode *e));
void PrintTree(BinTree T);
int updateHeight(BinNode *x);
void updateHeightAbove(BinNode *x);
void travIn(BinTree T,void visit(BinNode *e));
void travPre(BinTree T,void visit(BinNode *e));
void visit(BinNode *e);
void writeToDot(BinTree T,char opt[],char info[]);

//栈数据结构
struct BinTreeStack{
    BinNode **elem;
    int size;
    int capacity;
};
typedef struct BinTreeStack BinTreeStack;
static BinTreeStack binTreeInitStack(void);
static void binTreePush(BinTreeStack *S, BinNode *e);
static BinNode *binTreePop(BinTreeStack *S);


//队列数据结构
struct BinTreeQueueNode{
    BinNode *data;
    struct BinTreeQueueNode *pred;
    struct BinTreeQueueNode *succ;
};
struct BinTreeQueue{
    int size;
    struct BinTreeQueueNode *header;
    struct BinTreeQueueNode *trailer;
};
typedef struct BinTreeQueueNode BinTreeQueueNode;
typedef struct BinTreeQueue BinTreeQueue;
static BinTreeQueue binTreeInitQueue(void);
static void binTreeEnqueue(BinTreeQueue *Q, BinNode *e);
static BinNode *binTreeDequeue(BinTreeQueue *Q);






#endif /* binTree_h */
