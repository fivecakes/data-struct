//
//  BTree.c
//  data-struct
//
//  Created by book on 2020/6/19.
//  Copyright © 2020 book. All rights reserved.
//

#include "BTree.h"


BTVector btree_init_vector()
{
    BTVector V;
    V.elem = malloc(2* sizeof(BTNode*));
    V.capacity =2;
    V.size = 0;
    return V;
}


//扩容
static void btree_expand(BTVector *V)
{
    if(V->size < V->capacity) return; //尚未满员，不必扩容
    V->elem = realloc(V->elem,(V->capacity<<=1)*sizeof(BTNode*));
}


//插入
void btree_insert(BTVector *V, int r, BTNode* e)
{
    btree_expand(V);
    for (int i = V->size; i>r; i--) {
        *(V->elem+i) = *(V->elem+i-1);
    }
    *(V->elem+r) = e;
    V->size++;
}

BTNode *btree_get(BTVector *V,int r)
{
    return *(V->elem + r);
}

//删除
void btree_delete_vector(BTVector *V, int r)
{
    for (int i = r; i<V->size -1; i++) {
        *(V->elem+i) = *(V->elem+i+1);
    }
    V->size--;
}



static void printDotNode(FILE* fp ,BTNode *e)
{
    if (!e || !(e->key.size)) {
        return;
    }
    fprintf(fp, " node%p [label = \"",e);
    for (int i=0; i<e->key.size; i++) {
        if (i) {
            fprintf(fp, "|");
        }
        fprintf(fp, " <node%d> %d", get(&e->key,i),get(&e->key,i));
    }
    fprintf(fp, "\"]\n");
    
    for (int i=0; i<e->child.size; i++) {
        
        if (btree_get(&e->child,i)) {
            if (i) {
                fprintf(fp, " node%p:<node%d>:se -> node%p\n", e,get(&e->key,i), btree_get(&e->child,i));
            }else {
                fprintf(fp, " node%p:<node%d>:sw -> node%p\n", e,get(&e->key,i), btree_get(&e->child,i));
            }
            
            printDotNode(fp,btree_get(&e->child,i));
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
    //fprintf(fp, " n%dh%d\n [label=\"top\"][style = dotted]\n", T.top->data,T.top->height);
    fprintf(fp, " splines=false;\n");
    fprintf(fp, " node [shape = record,height=.1,style=filled,color=lightblue;];\n\n");

//    if (T.top->lChild) {
//        fprintf(fp, " n%dh%d -> n%dh%d\n", T.top->data,T.top->height, T.top->lChild->data,T.top->lChild->height) ;
//        fprintf(fp, " n%dh%d -> n%dh%d\n",  T.top->lChild->data,T.top->lChild->height,T.top->lChild->parent->data,T.top->lChild->parent->height) ;
//
//        printDotNode(fp ,T.top->lChild);
//    }
    printDotNode(fp ,BT.root);
    fprintf(fp, "}\n");
    fclose(fp);
}
