#ifndef huffman_h
#define huffman_h
#include "common.h"


struct huff_char{
    char ch;
    int weight;
};

struct huff_tree_node{
    struct huff_tree_node *parent;
    struct huff_tree_node *left_child;
    struct huff_tree_node *right_child;
    struct huff_char data;
};

struct huff_tree{
    int size;
    struct huff_tree_node *top;
    struct huff_tree_node *hot;
};



struct huff_forest_node{
    struct huff_tree data;
    struct huff_forest_node *pred;
    struct huff_forest_node *succ;
};

struct huff_forest{
    int size;
    struct huff_forest_node *header;
    struct huff_forest_node *trailer;
};



#endif
