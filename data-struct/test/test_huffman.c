#include "test_huffman.h"



void test_huffman(void)
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
//    struct huff_forest forest = generate_forest("AAABBACCCDEEA");
//    struct huff_tree huff_tree = generate_tree(&forest);
    //解码
    //huffman_decode(&huff_tree, &code);
}
