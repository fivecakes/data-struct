#ifndef binTree_h
#define binTree_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NULL ((void*)0)


#define stature(p) ((p) ? (p)->height : -1)
#define max(a,b) ((a)>(b)?(a):(b))

struct TreeNode{
    int data;
    struct TreeNode *parent;
    struct TreeNode *lChild;
    struct TreeNode *rChild;
    int height;
    int npl;
    int color;
};

struct BinTree{
    int size;
    struct TreeNode *header; //哨兵节点
};

typedef struct TreeNode TreeNode;
typedef struct BinTree BinTree;

TreeNode *insertAsRC(TreeNode *x, int e);
TreeNode *insertAsLC(TreeNode *x, int e);
BinTree initBinTree(void);
void travLevel(BinTree T,void visit(TreeNode *e));
void PrintTree(BinTree T);
int updateHeight(TreeNode *x);
void updateHeightAbove(TreeNode *x);
void travIn(BinTree T,void visit(TreeNode *e));
void travPre(BinTree T,void visit(TreeNode *e));
void visit(TreeNode *e);
void writeTreeToDotFile(BinTree T,char opt[],char info[]);

//栈数据结构
struct BinTreeStack{
    TreeNode **elem;
    int size;
    int capacity;
};
typedef struct BinTreeStack BinTreeStack;


//队列数据结构
struct BinTreeQueueNode{
    TreeNode *data;
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


#endif /* binTree_h */
