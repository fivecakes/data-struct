#ifndef binTree_h
#define binTree_h
#include "common.h"
#define stature(p) ((p) ? (p)->height : -1)

struct tree_node{
    struct tree_node *parent;
    struct tree_node *left_child;
    struct tree_node *right_child;
    //数据
    int data;
    //其他指标
    int height;
    int npl;
    int color;
};

struct tree{
    int size;
    struct tree_node *top;
    struct tree_node *hot;
};


struct tree init_tree(void);
void level_traversal(struct tree T,void visit(struct tree_node *e));
void in_traversal(struct tree T,void visit(struct tree_node *e));
void pre_traversal(struct tree T,void visit(struct tree_node *e));
void visit(struct tree_node *e);
void write_tree_to_dotfile(struct tree *T,char opt[],char info[]);

//栈数据结构
struct tree_stack{
    struct tree_node **elem;
    int size;
    int capacity;
};


//队列数据结构
struct tree_queue_node{
    struct tree_node *data;
    struct tree_queue_node *pred;
    struct tree_queue_node *succ;
};
struct tree_queue{
    int size;
    struct tree_queue_node *header;
    struct tree_queue_node *trailer;
};


#endif /* binTree_h */
