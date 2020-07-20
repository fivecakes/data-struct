#include "huffman.h"


void generate_code_table (char* code, int length, struct hash_table* table, struct huff_tree_node* v )
{
   if (!v->left_child){
       code[length] = '\0';
       char key[] = {v->huff_char.ch,'\0'};
       hash_insert(table, key, code);
       return;
   }
   if (v->left_child){//Left = 0
       code[length] = '0';
       generate_code_table ( code,  length+1,table, v->left_child );
   }
   if (v->right_child){//Right = 1
       code[length] = '1';
       generate_code_table ( code,  length+1,table, v->right_child );
   }
}

struct hash_table* generate_table (struct huff_tree* tree)
{
    struct hash_table *table = malloc(sizeof(struct hash_table));
    init_hash_table(table);
    
    char code[100];
    generate_code_table(code,0,table, tree->top);
    return table;
};


struct huff_tree creat_huff_tree(char ch,int weight)
{
    struct huff_char huff_char;
    huff_char.ch = ch;
    huff_char.weight = weight;
    
    
    
    struct huff_tree_node *huff_tree_node = malloc(sizeof(struct huff_tree_node));
    huff_tree_node->parent = NULL;
    huff_tree_node->left_child = NULL;
    huff_tree_node->right_child = NULL;
    huff_tree_node->huff_char = huff_char;
    
    struct huff_tree t;
    t.size = 0;
    t.top = huff_tree_node;

    return t;
}






void huff_forest_insert(struct huff_forest *f,struct huff_tree tree)
{
    struct huff_forest_node *new = malloc(sizeof(struct huff_forest_node));
    new->huff_tree = tree;
    
    struct huff_forest_node *p = f->trailer;
    struct huff_forest_node *h = p->pred;
    
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
    
    f->size++;
}




struct huff_tree* min_huff_char ( struct huff_forest* f )
{
    //首节点
    struct huff_forest_node *p =f->header->succ;
    
    //记录权重最小节点的位置及权重
    struct huff_forest_node *minChar = p;
    int minWeight = p->huff_tree.top->huff_char.weight;
    
    //遍历所有节点
    while(p->succ){
        if (minWeight > p->huff_tree.top->huff_char.weight ){
            minWeight = p->huff_tree.top->huff_char.weight;
            minChar = p;
        }
        p = p->succ;
    }
    
    //从森林中删除
    minChar->pred->succ = minChar->succ;
    minChar->succ->pred = minChar->pred;
    f->size--;
    return &(minChar->huff_tree);
}

int* statistics ( char* sample_text_file )
{
    int* freq = malloc(N_CHAR* sizeof(int));
    memset ( freq, 0, sizeof ( int ) * N_CHAR );
    FILE* fp = fopen ( sample_text_file, "r" );
    for ( char ch; 0 < fscanf ( fp, "%c", &ch );)
        if ( ch >= 0x20 ) freq[ch - 0x20]++;
    fclose ( fp );
    return freq;
}

struct huff_forest* initForest ( int* freq )
{
    struct huff_forest* forest = malloc(sizeof(struct huff_forest));
    forest->size = 0;
    forest->header = malloc(sizeof(struct huff_forest_node));
    forest->trailer = malloc(sizeof(struct huff_forest_node));
    forest->header->pred = NULL;
    forest->trailer->succ = NULL;
    forest->trailer->pred = forest->header;
    forest->header->succ = forest->trailer;
    
    for ( int i = 16; i < N_CHAR; i++ ) {
        //新树
        struct huff_tree new_huff_tree = creat_huff_tree(0x20 + i,freq[i]);
        
        //将新树加入森林
        huff_forest_insert(forest,new_huff_tree);
    }
    return forest;
}


struct huff_tree* generate_tree(struct huff_forest* forest)
{
    while ( 1 < forest->size ) {
        //从森林里面选取两颗权重最低的树，并将这两科树从森林中删除
        struct huff_tree* T1 = min_huff_char ( forest );
        struct huff_tree* T2 = min_huff_char ( forest );
        
        //将这两颗树组成一棵新树
        struct huff_tree new_huff_tree = creat_huff_tree('^',T1->top->huff_char.weight + T2->top->huff_char.weight);
        new_huff_tree.top->left_child = T1->top;
        T1->top->parent = new_huff_tree.top;
        new_huff_tree.top->right_child = T2->top;
        T2->top->parent = new_huff_tree.top;
        
        //将新树加入森林
        huff_forest_insert(forest,new_huff_tree);
    }
    return &forest->header->succ->huff_tree;
}


//根据编码表，将字符串转换为二进制编码
char *huffman_encode(struct hash_table* table, char* s)
{
    char * code = malloc(200*sizeof(char));
    char c[] = {' ','\0'};
    int len = 0;
    for ( size_t m = strlen (s), i = 0; i < m; i++ ) {
        //对每个字符从编码表中获取编码
        c[0] = s[i];
        char* pCharCode = hash_get(table, c);
        //不能识别的用空格代替
        if ( !pCharCode ) pCharCode = hash_get (table, " " );
        
        for ( size_t m = strlen (pCharCode), j = 0; j < m; j++ ){
            code[len++] = * (pCharCode + j);
        }
    }
    code[len+1] = '\0';
    return code;
}


void huffman_decode(struct huff_tree* tree,char * code)
{
    struct huff_tree_node *x = tree->top;
    for ( int i = 0; i < strlen(code); i++ ) {
        if (code[i] == '1') {
            x = x->right_child;
        }else{
            x = x->left_child;
        }

        if (!x->left_child) {
          printf ("%c", x->huff_char.ch );
          x = tree->top;
        }
    }
    printf("\n");
}



static void huff_print_dot_node(FILE* fp ,struct huff_tree_node *e)
{
    if (!e) return;
    fprintf(fp, " node%p[label=\" %c \"]\n", e,e->huff_char.ch);
    
    
    if (!e->left_child && !e->right_child) {
        return;
    }
    
    if (e->left_child) {
        fprintf(fp, " node%p -> node%p\n", e ,e->left_child) ;
        fprintf(fp, " node%p -> node%p\n",  e->left_child,e->left_child->parent) ;
        huff_print_dot_node(fp ,e->left_child);
    }else{
        fprintf(fp, " lChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> lChild%p[style = dotted]\n", e,e);
    }
    
    if (e->right_child) {
        fprintf(fp, " node%p -> node%p\n", e ,e->right_child) ;
        fprintf(fp, " node%p -> node%p\n",  e->right_child,e->right_child->parent) ;
        huff_print_dot_node(fp ,e->right_child);
    }else{
        fprintf(fp, " rChild%p [label=\"Null\"][style = dotted]\n", e);
        fprintf(fp, " node%p -> rChild%p[style = dotted]\n", e,e);
    }
}

static void print_dot_forest(FILE* fp ,struct huff_forest *forest)
{
    //记录权重最小节点的位置及权重
    struct huff_forest_node *p = forest->header->succ;
    
    //遍历所有节点
    while(p->succ){
        fprintf(fp, " node [shape=\"box\",style=filled,color=\"#8139e5ff\"]\n");
        fprintf(fp, " edge [color=\"#8139e5ff\",minlen=\"10\"]\n");
        fprintf(fp, " node%p[label=\"\"]\n", p);
        if (p->succ->succ) {
            fprintf(fp, " node%p->node%p[dir=\"both\"]\n",p,p->succ);
            fprintf(fp, " {rank=same; node%p;node%p}\n",p,p->succ);
        }
        fprintf(fp, " node [shape= ellipse,style=filled,color=lightblue]\n");
        fprintf(fp, " edge [color=lightblue,minlen=\"1\"];\n");
        fprintf(fp, " node%p->node%p\n",p,p->huff_tree.top);
        
        huff_print_dot_node(fp ,p->huff_tree.top);
        p = p->succ;
    }
}

void write_huff_tree_to_dotfile(struct huff_forest *forest,char opt[],char info[])
{
    FILE* fp = fopen(DOT_FILE_PATH, opt);
    if( NULL == fp)
    {
        printf("打开文件描述符失败\n");
        fprintf(stderr, "打开文件描述符失败\n");
        return;
    }
    fprintf(fp, "\n//%s",info);
    fprintf(fp, "\ndigraph {\n");
    print_dot_forest(fp ,forest);
    fprintf(fp, "}\n");
    fclose(fp);
}
