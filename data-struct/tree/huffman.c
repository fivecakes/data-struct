#include "huffman.h"

struct huff_tree init_huff_tree()
{
    struct huff_tree t;
    t.top = NULL;
    t.size = 0;
    t.hot = NULL;
    
    return t;
}


struct huff_tree_node *insert_huff_tree_root(struct huff_tree *t,struct huff_char e)
{
    struct huff_tree_node *huff_tree_node = malloc(sizeof(struct huff_tree_node));
    huff_tree_node->parent = NULL;
    huff_tree_node->left_child = NULL;
    huff_tree_node->right_child = NULL;
    huff_tree_node->data = e;

    t->top = huff_tree_node;

    return huff_tree_node;
}






void huff_forest_insert(struct huff_forest *f,struct huff_tree e)
{
    struct huff_forest_node *p = f->trailer;
    struct huff_forest_node *new = malloc(sizeof(struct huff_forest_node));
    struct huff_forest_node *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
}




struct huff_tree* min_huff_char ( struct huff_forest* f ) {
    //首节点
    struct huff_forest_node *p =f->header->succ;
    
    //记录权重最小节点的位置及权重
    struct huff_forest_node *minChar = p;
    int minWeight = p->data.top->data.weight;
    
    //遍历所有节点
    while(p->succ->succ){
        if (minWeight > p->data.top->data.weight ){
            minWeight = p->data.top->data.weight;
            minChar = p;
        }
        p = p->succ;
    }
    
    //从森林中删除
    minChar->pred->succ = minChar->succ;
    minChar->succ->pred = minChar->pred;

    return &minChar->data;
}


struct huff_tree generate_tree (struct huff_forest* forest ) {
    while ( 1 < forest->size ) {
        //从森林里面选取两颗权重最低的树，并将这两科树从森林中删除
        struct huff_tree* T1 = min_huff_char ( forest );
        struct huff_tree* T2 = min_huff_char ( forest );
        
        //将这两颗树组成一棵新树
        struct huff_tree new_huff_tree = init_huff_tree();
        struct huff_char huff_char;
        huff_char.ch ='^';
        huff_char.weight = T1->top->data.weight + T2->top->data.weight;
        insert_huff_tree_root(&new_huff_tree,huff_char);
        new_huff_tree.top->left_child = T1->top;
        T1->top->parent = new_huff_tree.top;
        new_huff_tree.top->right_child = T2->top;
        T2->top->parent = new_huff_tree.top;
        
        //将新树加入森林
        huff_forest_insert(forest,new_huff_tree);
    }
    return forest->header->pred->data;
}
