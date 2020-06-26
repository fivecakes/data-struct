//
//  BTree.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BTree.h"


BTVector btree_vector_init()
{
    BTVector V;
    V.elem = malloc(2* sizeof(BTNode*));
    V.capacity =2;
    V.size = 0;
    return V;
}


//扩容
static void btree_vector_expand(BTVector *V)
{
    if(V->size < V->capacity) return; //尚未满员，不必扩容
    V->elem = realloc(V->elem,(V->capacity<<=1)*sizeof(BTNode*));
}

void btree_vector_insert(BTVector *V, int r, BTNode* e)
{
    btree_vector_expand(V);
    for (int i = V->size; i>r; i--) {
        *(V->elem+i) = *(V->elem+i-1);
    }
    *(V->elem+r) = e;
    V->size++;
}


BTNode *btree_vector_get(BTVector *V,int r)
{
    return *(V->elem + r);
}

//删除
void btree_vector_delete(BTVector *V, int r)
{
    for (int i = r; i<V->size -1; i++) {
        *(V->elem+i) = *(V->elem+i+1);
    }
    V->size--;
}

BTree btree_init()
{
    
    
    BTNode *node = malloc(sizeof(BTNode));
    
    node->parent = NULL;
    
    node->key.elem = malloc(2* sizeof(int));
    node->key.capacity = 2;
    node->key.size = 0;
    
    node->child.elem = malloc(2* sizeof(BTNode*));
    node->child.capacity = 2;
    node->child.size = 0;
    
    BTree BT;
    BT.size = 1;
    BT.hot = NULL;
    BT.root = node;
    btree_vector_insert(&BT.root->child, 0, NULL);
    
    return BT;
}


BTNode *btree_search(BTree *BT,int e)
{
    BTNode *v = BT->root;
    BT->hot = NULL;
    
    while (v) {
        int r = vector_search(&v->key,e);
        if (r>=0 && vector_get(&v->key, r) == e) return v;
        BT->hot = v;
        //此步模拟I/O操作，
        v= btree_vector_get(&v->child,r+1);
    }
    
    return NULL;
}

void solveOverflow(BTNode *v)
{
    
}


int btree_insert(BTree *BT,int e)
{
    BTNode *v = btree_search(BT,e);
    if (v) {
        printf("%d存在\n",e);
        return 1;
    }
    
    int r = vector_search(&BT->hot->key,e);
    vector_insert(&BT->hot->key, r+1, e);
    btree_vector_insert(&BT->hot->child, r+2, NULL);
    
    BT->size++;
    //solveOverflow(BT.hot);
    
    return 1;
}

static void printDotNode1(FILE* fp ,BTNode *e)
{
    if (!e || !(e->key.size)) {
        return;
    }
    fprintf(fp, " node%p [label = \"",e);
    for (int i=0; i<e->key.size; i++) {
        if (i) {
            fprintf(fp, "|");
        }
        fprintf(fp, " <node%d> %d", vector_get(&e->key,i),vector_get(&e->key,i));
    }
    fprintf(fp, "\"]\n");
    
    for (int i=0; i<e->child.size; i++) {
        
        if (btree_vector_get(&e->child,i)) {
            if (i) {
                fprintf(fp, " node%p:<node%d>:se -> node%p\n", e,vector_get(&e->key,i), btree_vector_get(&e->child,i));
            }else {
                fprintf(fp, " node%p:<node%d>:sw -> node%p\n", e,vector_get(&e->key,i), btree_vector_get(&e->child,i));
            }
            
            printDotNode1(fp,btree_vector_get(&e->child,i));
        }
    }
}



void writeBTreeToDotFile(BTree BT,char opt[],char info[])
{
    FILE* fp = fopen("/Users/book/Codes/data-struct/data-struct/tree.dot", opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//%s",info);
    fprintf(fp, "\ndigraph {\n");
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [shape = record,height=.1,style=filled,color=lightblue;];\n\n");

    printDotNode1(fp ,BT.root);
    fprintf(fp, "}\n");
    fclose(fp);
}
