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

struct Tree{
    int size;
    struct TreeNode *top; //哨兵节点
};

typedef struct TreeNode TreeNode;
typedef struct Tree Tree;

TreeNode *insertAsRC(TreeNode *x, int e);
TreeNode *insertAsLC(TreeNode *x, int e);
Tree initBinTree(void);
void travLevel(Tree T,void visit(TreeNode *e));
void PrintTree(Tree T);
int updateHeight(TreeNode *x);
void updateHeightAbove(TreeNode *x);
void travIn(Tree T,void visit(TreeNode *e));
void travPre(Tree T,void visit(TreeNode *e));
void visit(TreeNode *e);
void writeTreeToDotFile(Tree T,char opt[],char info[]);

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
