#include "hash_table.h"


//初始化哈希表
void init_hash_table(table* t)
{
    int i;
    if (t == NULL)return;

    for (i = 0; i < BUCKETCOUNT; ++i) {
        t->bucket[i].key = NULL;
        t->bucket[i].value = NULL;
        t->bucket[i].next = NULL;
    }
}

//近似多项式法，将字符串转换为数字
int hash_code(char* s)
{
    int h = 0;
    for (size_t n = strlen(s),i = 0; i<n; i++) {
        h = (h<<5) | (h>>27);
        h += (int)s[i];
    }
    printf("%s = %d\n",s,h);
    return h;
}

// 散列函数
// hash(key) = ((a*key)+b)%M
int mad(int key)
{
    int a = 3;
    int b = 2;
    return ((a*key)+b)%BUCKETCOUNT;
}


int key2index(char* key)
{
    return mad(hash_code(key));
}


//向哈希表中插入数据
int insert_entry(table* t , char* key , char* value)
{
    int index, vlen1, vlen2;
    entry *e, *ep;

    index = key2index(key);
    if (t->bucket[index].key == NULL) {
        t->bucket[index].key = strdup(key);
        t->bucket[index].value = strdup(value);
    } else {
        e = ep = &(t->bucket[index]);
        while (e != NULL) { //先从已有的找,找到后替换
            if (strcmp(e->key , key) == 0) {
                //找到key所在，替换值
                vlen1 = (int)strlen(value);
                vlen2 = (int)strlen(e->value);
                if (vlen1 > vlen2) {
                    free(e->value);
                    e->value = (char*)malloc(vlen1 + 1);
                }
                memcpy(e->value , value , vlen1 + 1);
                return index;   //插入完成了
            }
            ep = e;
            e = e->next;
        }
        //没有在当前桶中找到
        //创建条目加入
        e = (entry*)malloc(sizeof (entry));
        e->key = strdup(key);
        e->value = strdup(value);
        e->next = NULL;
        ep->next = e;
    }
    return index;
}

//在哈希表中查找key对应的value
//找到了返回value的地址，没找到返回NULL
char* find_value_by_key(table* t , char* key)
{
    int index;
    entry* e;
    if (t == NULL || key == NULL) {
        return NULL;
    }
    index = key2index(key);
    e = &(t->bucket[index]);
    if (e->key == NULL) return NULL;//这个桶还没有元素
    while (e != NULL) {
        if (0 == strcmp(key , e->key)) {
            return e->value;    //找到了，返回值
        }
        e = e->next;
    }
    return NULL;
}



