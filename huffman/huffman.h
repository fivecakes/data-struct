#ifndef huffman_h
#define huffman_h
#include "../common.h"
#include <string.h>
#include "../hash_table/hash_table.h"
#include "../linear/vector.h"

#define  N_CHAR  (0x80 - 0x20)

struct huff_char{
    char ch;
    int weight;
};

struct huff_tree_node{
    struct huff_tree_node *parent;
    struct huff_tree_node *left_child;
    struct huff_tree_node *right_child;
    struct huff_char huff_char;
};

struct huff_tree{
    int size;
    struct huff_tree_node *top;
    struct huff_tree_node *hot;
};



struct huff_forest_node{
    struct huff_tree huff_tree;
    struct huff_forest_node *pred;
    struct huff_forest_node *succ;
};

struct huff_forest{
    int size;
    struct huff_forest_node *header;
    struct huff_forest_node *trailer;
};


struct huff_forest generate_forest(char* s);
struct huff_tree* generate_tree(struct huff_forest* forest);
char *huffman_encode(struct hash_table* table, char* s);
void huffman_decode(struct huff_tree* tree,char * code);
int* statistics ( char* sample_text_file );
struct huff_forest* init_forest ( int* freq );
void write_huff_tree_to_dotfile(struct huff_forest *forest,char opt[],char info[]);
struct hash_table* generate_table (struct huff_tree* tree);











#endif
