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

//特殊的：对于指针类型的遍历搜索
int btree_vector_search(BTVector *V, BTNode* e)
{
    for (int i = 0; i<V->size; i++) {
        if (*(V->elem+i) == e) {
            return i;
        }
    }
    return -1;
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
    BT.order = 5;
    
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
    //writeBTreeToDotFile(BT,"a+","分裂之前");
    BTNode *p = v->parent;
    int mid = v->key.size/2;//c语言中整数/整数还是整数，自动强制类型转换了
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

void solveUnderflow(BTree *BT,BTNode *v)
{
    writeBTreeToDotFile(BT,"a+","solveUnderflow");
    //向上取整c = (a + b - 1) / b;
    int under = (BT->order + 2 - 1) / 2;
    
    if (v->child.size >= under) return;
    
    //r是父节点child的秩，父节点key的秩是r-1
    int r = btree_vector_search(&v->parent->child,v);
    BTNode *brother;
    if (r>0 && btree_vector_get(&v->parent->child, r-1)->child.size > under) {
        printf("向左兄弟借一个\n");
        
        //三角借债，先向父亲借，然后左兄弟给父亲,注意：父亲和兄弟都分左右
        brother = btree_vector_get(&v->parent->child, r-1);
        
        //从父亲拿值
        vector_insert(&v->key,0,vector_get(&v->parent->key,r-1));
        //从兄弟拿指针
        btree_vector_insert(&v->child,0,btree_vector_get(&brother->child,brother->child.size-1));
        //兄弟给父亲
        vector_replace(&v->parent->key,r-1,vector_get(&brother->key,brother->key.size-1));
        //删掉兄弟
        vector_delete(&brother->key,brother->key.size-1);
        btree_vector_delete(&brother->child,brother->child.size-1);
        
    }else if ((r+1) < v->parent->child.size && btree_vector_get(&v->parent->child, r+1)->child.size > under){
        printf("向右兄弟借一个\n");
        //三角借债，先向父亲借，然后左兄弟给父亲，注意：父亲和兄弟都分左右
        brother = btree_vector_get(&v->parent->child, r+1);
        
        //从父亲拿值
        vector_insert(&v->key,v->key.size,vector_get(&v->parent->key,r));
        //从兄弟拿指针
        btree_vector_insert(&v->child,v->child.size,btree_vector_get(&brother->child,0));
        //兄弟给父亲
        vector_replace(&v->parent->key,r,vector_get(&brother->key,0));
        //删掉兄弟
        vector_delete(&brother->key,0);
        btree_vector_delete(&brother->child,0);
    }else{
        if (r>0) {
            printf("左兄弟存在，与左兄弟合并\n");
            brother = btree_vector_get(&v->parent->child, r-1);
            
            //父亲插入到左兄弟
            vector_insert(&brother->key,brother->key.size,vector_get(&v->parent->key,r-1));

            //v插入到左兄弟
            for (int i = 0; i<v->key.size; i++) {
                vector_insert(&brother->key,brother->key.size,vector_get(&v->key,i));
                btree_vector_insert(&brother->child,brother->child.size,btree_vector_get(&v->child,i));
            }

            btree_vector_insert(&brother->child,brother->child.size,btree_vector_get(&v->child,v->key.size));

            //删除父亲
            vector_delete(&v->parent->key,r);
            btree_vector_delete(&v->parent->child,r);
        }else{
            printf("左兄弟不存在，与右兄弟合并\n");
            brother = btree_vector_get(&v->parent->child, r+1);
            
            //父亲插入到左兄弟
            vector_insert(&brother->key,0,vector_get(&v->parent->key,r));
            
            //v插入到左兄弟
            for (int i = v->key.size-1; i>=0; i--) {
                vector_insert(&brother->key,0,vector_get(&v->key,i));
                btree_vector_insert(&brother->child,0,btree_vector_get(&v->child,i+1));
            }
            btree_vector_insert(&brother->child,0,btree_vector_get(&v->child,0));
            //删除父亲
            vector_delete(&v->parent->key,r);
            btree_vector_delete(&v->parent->child,r);
        }
        if (!v->parent->parent) {
            printf("合并根节点！\n");
            BT->root = brother;
            brother->parent = NULL;
        }else{
            solveUnderflow(BT, v->parent);
        }
    }
    
    
}


void btree_insert(BTree *BT,int e)
{
    BTNode *v = btree_search(BT,e);
    if (v) {
        printf("%d存在,插入失败\n",e);
    }
    
    int r = vector_search(&BT->hot->key,e);
    //printf("插入到第%d\n",r+1);
    vector_insert(&BT->hot->key, r+1, e);
    btree_vector_insert(&BT->hot->child, r+2, NULL);
    
    BT->size++;
    
    solveOverflow(BT,BT->hot);
    
}


void btree_remove(BTree *BT,int e)
{
    BTNode *v = btree_search(BT,e);
    if (!v) {
        printf("%d不存在,删除失败\n",e);
    }
    //确定e在v中的秩
    int r = vector_search(&v->key,e);
    if(btree_vector_get(&v->child, 0)){
        //若v非叶节点,找到e的后继，并与之交换
        BTNode *u = btree_vector_get(&v->child, r+1);//右子树
        while (btree_vector_get(&u->child, 0)) {
            u = btree_vector_get(&u->child, 0);
        }
        //将e的后继放到e的位置
        vector_replace(&v->key,r,vector_get(&u->key, 0));
        //后面要把e的后继删掉，但是u变量不能在if外用，所以v指向u
        v = u;r=0;
    }
    vector_delete(&v->key, r);
    btree_vector_delete(&v->child, r+1);
    BT->size--;
    
    solveUnderflow(BT,v);
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
//            fprintf(fp, " Null%p%d [label=\"Null\"][style = dotted]\n",e, i);
//            if (!i) {
//                fprintf(fp, " node%p:<node%d>:sw -> Null%p%d[style = dotted]\n", e,vector_get(&e->key,i),e,i);
//            }else {
//                fprintf(fp, " node%p:<node%d>:se -> Null%p%d[style = dotted]\n", e,vector_get(&e->key,i-1),e,i);
//            }
            
        }
    }
}



void writeBTreeToDotFile(BTree *BT,char opt[],char info[])
{
    FILE* fp = fopen(dot_file_path, opt);
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
