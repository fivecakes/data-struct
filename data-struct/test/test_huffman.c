#include "test_huffman.h"

void test_huffman()
{
    //创建huffman树
    int* freq = statistics ("/Users/book/Codes/data-struct/data-struct/huffman/sample.txt");
    struct huff_forest *forest = initForest(freq);
    struct huff_tree* huff_tree = generate_tree(forest);
    write_huff_tree_to_dotfile(forest,"w+","");

    //根据huffman树，生成编码表
    struct hash_table* table = generate_table(huff_tree);
    printf("A = %s\n",hash_get(table, "A"));
    printf("B = %s\n",hash_get(table, "B"));
    printf("C = %s\n",hash_get(table, "C"));
    printf("D = %s\n",hash_get(table, "D"));
    printf("E = %s\n",hash_get(table, "E"));
    
    //编码
    char * code = huffman_encode(table,"AAABBACCCDEEA");
    printf("%s\n",code);
    //解码
    huffman_decode(huff_tree, code);
}
