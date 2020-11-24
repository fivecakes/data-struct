#include "list.h"



struct list list_init()
{
    struct list list;
    list.size = 0;
    list.header = malloc(sizeof(struct list_node));
    list.trailer = malloc(sizeof(struct list_node));
    list.trailer->pred = list.header;
    list.header->succ = list.trailer;
    return list;
}

int list_get(struct list list,int r)
{
    struct list_node *p = list.header;
    while (r--) {
        p = p->succ;
    }
    return p->pred->data;
}


void list_insert_before(struct list_node *p,int e)
{
    struct list_node *new = malloc(sizeof(struct list_node));
    struct list_node *h = p->pred;
    
    new->data = e;
    h->succ =new;
    p->pred = new;
    new->pred = h;
    new->succ = p;
}


void list_insert(struct list *list, int n, int e)
{
    struct list_node *p = list->header->succ;
    while (n) {
        p=p->succ;
        n--;
    }
    list_insert_before(p,e);
    list->size++;
}


//取出前n个中最大的
static struct list_node* select_max(struct list *list, int n)
{
    struct list_node *p = list->header->succ;
    struct list_node *max = p;
    
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
void list_selection_sort(struct list *list)
{
    struct list_node* p;
    struct list_node* t = list->trailer->pred;
    int tmp;
    
    for (int i = list->size; i>0; i--) {
        p = select_max(list, i);
        tmp = p->data;
        p->data = t->data;
        t->data = tmp;
        
        t=t->pred;
    }
}


static struct list_node* search(struct list_node *p, int n, int e)
{
    p = p->pred;
    while (n && (p->data>e)) {
        p = p->pred;
        n--;
    }
    return p;
}



static void move_after(struct list_node *p,struct list_node *s)
{
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    
    p->succ = s->succ;
    p->pred = s;
    s->succ->pred = p;
    s->succ = p;
}

//插入排序
void list_insert_sort(struct list *list)
{
    struct list_node *c = list->header->succ->succ->succ;
    struct list_node *s,*p;
    
    for (int i = 1; i<list->size; i++) {
        p = c->pred;
        s = search(p,i,p->data);
        move_after(p, s);
        c = c->succ;
    }
}


void list_write2dot(struct list list,char opt[],char info[])
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
    fprintf(fp, " rankdir = LR\n");
    fprintf(fp, " node0 [label=\"header\"][style = dotted]\n");
    struct list_node *v = list.header->succ;
    for (int i = 0; i<list.size; i++) {
        fprintf(fp, " node%d[label=\"%d\"]\n",i+1,v->data);
        fprintf(fp, " node%d -> node%d\n",i,i+1);
        fprintf(fp, " node%d -> node%d\n",i+1,i);
        v = v->succ;
    }
    
    fprintf(fp, " node%d [label=\"trailer\"][style = dotted]\n",list.size+1);
    fprintf(fp, " node%d -> node%d\n",list.size,list.size+1);
    fprintf(fp, " node%d -> node%d\n",list.size+1,list.size);
    
    fprintf(fp, "}\n");
    fclose(fp);
}
