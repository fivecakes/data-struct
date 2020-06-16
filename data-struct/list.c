#include "list.h"



static List initList()
{
    List L;
    L.size = 0;
    L.header = malloc(sizeof(ListNode));
    L.trailer = malloc(sizeof(ListNode));
    L.trailer->pred = L.header;
    L.header->succ = L.trailer;
    return L;
}

static int listGet(List L,int r)
{
    ListNode *p = L.header;
    while (r--) {
        p = p->succ;
    }
    return p->pred->data;
}


static void insertBefore(ListNode *p,int e)
{
    ListNode *new = malloc(sizeof(ListNode));
    ListNode *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
}


static void listInsert(List *L, int n, int e)
{
    ListNode *p = L->header->succ;
    while (n) {
        p=p->succ;
        n--;
    }
    insertBefore(p,e);
    L->size++;
}


//取出前n个中最大的
static ListNode* selectMax(List *L, int n)
{
    ListNode *p = L->header->succ;
    ListNode *max = p;
    
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
static void selectionSort(List *L)
{
    ListNode* p;
    ListNode* t = L->trailer->pred;
    int tmp;
    
    for (int i = L->size; i>0; i--) {
        p = selectMax(L, i);
        tmp = p->data;
        p->data = t->data;
        t->data = tmp;
        
        t=t->pred;
    }
}


static ListNode* search(ListNode *p, int n, int e)
{
    p = p->pred;
    while (n && (p->data>e)) {
        p = p->pred;
        n--;
    }
    return p;
}



static void moveAfter(ListNode *p,ListNode *s)
{
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    
    p->succ = s->succ;
    p->pred = s;
    s->succ->pred = p;
    s->succ = p;
}

//插入排序
static void insertSort(List *L)
{
    ListNode *c = L->header->succ->succ->succ;
    ListNode *s,*p;
    
    for (int i = 1; i<L->size; i++) {
        p = c->pred;
        s = search(p,i,p->data);
        moveAfter(p, s);
        c = c->succ;
    }
}

