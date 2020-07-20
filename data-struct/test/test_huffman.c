#include "test_huffman.h"



void test_huffman()
{
    //创建编码表
    struct hash_table t;
    init_hash_table(&t);
    hash_insert(&t , "A" , "0");
    hash_insert(&t , "B" , "101");
    hash_insert(&t , "C" , "111");
    hash_insert(&t , "D" , "100");
    hash_insert(&t , "E" , "110");
    
    //编码
    struct vector code = vector_init();
    huffman_encode(&t, &code, "AAABBACCCDEEA");
    
    //创建huffman树
    int* freq = statistics ("/Users/book/Codes/data-struct/data-struct/huffman/sample.txt");
    struct huff_forest *forest = initForest(freq);
    write_huff_tree_to_dotfile(forest,"w+","");
    struct huff_tree huff_tree = generate_tree(forest);
    write_huff_tree_to_dotfile(forest,"a+","");
    //解码
    huffman_decode(&huff_tree, &code);
    
}
