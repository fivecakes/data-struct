#ifndef binTree_h
#define binTree_h
#include "common.h"
#define stature(p) ((p) ? (p)->height : -1)

struct TreeNode{
    struct TreeNode *parent;
    struct TreeNode *lChild;
    struct TreeNode *rChild;
    //数据
    int data;
    //其他指标
    int height;
    int npl;
    int color;
};

struct Tree{
    int size;
    struct TreeNode *top;
    struct TreeNode *hot;
};


struct Tree initBinTree(void);
void travLevel(struct Tree T,void visit(struct TreeNode *e));
void travIn(struct Tree T,void visit(struct TreeNode *e));
void travPre(struct Tree T,void visit(struct TreeNode *e));
void visit(struct TreeNode *e);
void writeTreeToDotFile(struct Tree *T,char opt[],char info[]);

//栈数据结构
struct BinTreeStack{
    struct TreeNode **elem;
    int size;
    int capacity;
};


//队列数据结构
struct BinTreeQueueNode{
    struct TreeNode *data;
    struct BinTreeQueueNode *pred;
    struct BinTreeQueueNode *succ;
};
struct BinTreeQueue{
    int size;
    struct BinTreeQueueNode *header;
    struct BinTreeQueueNode *trailer;
};


#endif /* binTree_h */
