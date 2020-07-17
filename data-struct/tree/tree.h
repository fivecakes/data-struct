#ifndef binTree_h
#define binTree_h
#include "commom.h"
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

typedef struct TreeNode TreeNode;
typedef struct Tree Tree;

Tree initBinTree(void);
void travLevel(Tree T,void visit(TreeNode *e));
void travIn(Tree T,void visit(TreeNode *e));
void travPre(Tree T,void visit(TreeNode *e));
void visit(TreeNode *e);
void writeTreeToDotFile(Tree *T,char opt[],char info[]);

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
