#include "list.h"



struct List list_init()
{
    struct List L;
    L.size = 0;
    L.header = malloc(sizeof(struct ListNode));
    L.trailer = malloc(sizeof(struct ListNode));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

int list_get(struct List L,int r)
{
    struct ListNode *p = L.header;
    while (r--) {
        p = p->succ;
    }
    return p->pred->data;
}


void list_insert_before(struct ListNode *p,int e)
{
    struct ListNode *new = malloc(sizeof(struct ListNode));
    struct ListNode *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
}


void list_insert(struct List *L, int n, int e)
{
    struct ListNode *p = L->header->succ;
    while (n) {
        p=p->succ;
        n--;
    }
    list_insert_before(p,e);
    L->size++;
}


//取出前n个中最大的
static struct ListNode* selectMax(struct List *L, int n)
{
    struct ListNode *p = L->header->succ;
    struct ListNode *max = p;
    
    while (n-1) {
        p=p->succ;
        if (p->data >= max->data) {
            max = p;
        }
        n--;
    }
    return max;
}


//选择排序
void list_selection_sort(struct List *L)
{
    struct ListNode* p;
    struct ListNode* t = L->trailer->pred;
    int tmp;
    
    for (int i = L->size; i>0; i--) {
        p = selectMax(L, i);
        tmp = p->data;
        p->data = t->data;
        t->data = tmp;
        
        t=t->pred;
    }
}


static struct ListNode* search(struct ListNode *p, int n, int e)
{
    p = p->pred;
    while (n && (p->data>e)) {
        p = p->pred;
        n--;
    }
    return p;
}



static void moveAfter(struct ListNode *p,struct ListNode *s)
{
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    
    p->succ = s->succ;
    p->pred = s;
    s->succ->pred = p;
    s->succ = p;
}

//插入排序
void list_insert_sort(struct List *L)
{
    struct ListNode *c = L->header->succ->succ->succ;
    struct ListNode *s,*p;
    
    for (int i = 1; i<L->size; i++) {
        p = c->pred;
        s = search(p,i,p->data);
        moveAfter(p, s);
        c = c->succ;
    }
}


void list_write2dot(struct List L,char opt[],char info[])
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
    fprintf(fp, " rankdir = LR\n");
    fprintf(fp, " node0 [label=\"header\"][style = dotted]\n");
    struct ListNode *v = L.header->succ;
    for (int i = 0; i<L.size; i++) {
        fprintf(fp, " node%d[label=\"%d\"]\n",i+1,v->data);
        fprintf(fp, " node%d -> node%d\n",i,i+1);
        fprintf(fp, " node%d -> node%d\n",i+1,i);
        v = v->succ;
    }
    
    fprintf(fp, " node%d [label=\"trailer\"][style = dotted]\n",L.size+1);
    fprintf(fp, " node%d -> node%d\n",L.size,L.size+1);
    fprintf(fp, " node%d -> node%d\n",L.size+1,L.size);
    
    fprintf(fp, "}\n");
    fclose(fp);
}
