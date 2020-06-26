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
    BTNode *new = malloc(sizeof(BTNode));
    new->parent = NULL;
    new->key = vector_init();
    new->child = btree_vector_init();
    btree_vector_insert(&new->child, 0, NULL);
    
    BTree BT;
    BT.size = 1;
    BT.hot = NULL;
    BT.root = new;
    BT.order = 3;
    
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

void solveOverflow(BTree *BT,BTNode *v)
{
    if (v->key.size < BT->order) return;
    writeBTreeToDotFile(BT,"a+","分裂之前");
    BTNode *p = v->parent;
    int mid = (int)(v->key.size/2);
    int mid_value = vector_get(&v->key, mid);
    
    //新建一个节点，并将中位数以后的数据移到新节点
    BTNode *new = malloc(sizeof(BTNode));
    new->key = vector_init();
    new->child = btree_vector_init();
    for (int i = mid+1; i<v->key.size; i++) {
        int key_value = vector_get(&v->key, i);
        BTNode *child_value = btree_vector_get(&v->child, i);
        
        vector_insert(&new->key, new->key.size, key_value);
        btree_vector_insert(&new->child, new->child.size, child_value);
        if (child_value) child_value->parent = new;
    }
    
    //child比key多一个，所以多移动一次
    BTNode *last = btree_vector_get(&v->child, v->key.size);
    btree_vector_insert(&new->child, new->child.size,last);
    if (last) last->parent = new;
    
    if (!p) {
        printf("根节点分裂\n");
        
        //新建一个根节点，并把中位数移到其中
        BTNode *newroot = malloc(sizeof(BTNode));
        newroot->parent = NULL;
        newroot->key = vector_init();
        newroot->child = btree_vector_init();
        vector_insert(&newroot->key, 0, mid_value);
        BT->root = newroot;
        btree_vector_insert(&newroot->child, 0, v);
        btree_vector_insert(&newroot->child, 1, new);

        //将中位数移后的数据删除
        v->key.size = mid;
        v->child.size = mid+1;
        //设置父亲
        v->parent = newroot;
        new->parent = newroot;
        
    }else{
        printf("分裂\n");
        
        //把中位数移插入到父节点
        int r = vector_search(&p->key, mid_value);
        vector_insert(&p->key, r+1, mid_value);
        btree_vector_insert(&p->child, r+2, new);
        
        //将中位数移后的数据删除
        v->key.size = mid;
        v->child.size = mid+1;
        
        //设置新节点父亲
        new->parent = p;
        
        solveOverflow(BT,p);
    }
    
}


int btree_insert(BTree *BT,int e)
{
    BTNode *v = btree_search(BT,e);
    if (v) {
        printf("%d存在,插入失败\n",e);
        return 1;
    }
    
    int r = vector_search(&BT->hot->key,e);
    printf("插入到第%d\n",r+1);
    vector_insert(&BT->hot->key, r+1, e);
    btree_vector_insert(&BT->hot->child, r+2, NULL);
    
    BT->size++;
    
    solveOverflow(BT,BT->hot);
    
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
        BTNode *childnode = btree_vector_get(&e->child,i);
        if (childnode) {
            if (!i) {
                fprintf(fp, " node%p:<node%d>:sw -> node%p\n", e,vector_get(&e->key,i), childnode);
            }else {
                fprintf(fp, " node%p:<node%d>:se -> node%p\n", e,vector_get(&e->key,i-1), childnode);
            }
            
            printDotNode1(fp,childnode);
        }else{
            fprintf(fp, " Null%p%d [label=\"Null\"][style = dotted]\n",e, i);
            if (!i) {
                fprintf(fp, " node%p:<node%d>:sw -> Null%p%d[style = dotted]\n", e,vector_get(&e->key,i),e,i);
            }else {
                fprintf(fp, " node%p:<node%d>:se -> Null%p%d[style = dotted]\n", e,vector_get(&e->key,i-1),e,i);
            }
            
        }
    }
}



void writeBTreeToDotFile(BTree *BT,char opt[],char info[])
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

    printDotNode1(fp ,BT->root);
    fprintf(fp, "}\n");
    fclose(fp);
}
