#include "stack.h"

struct stack stack_init()
{
    struct stack s;
    s.elem = malloc(2* sizeof(int));
    s.capacity =2;
    s.size = 0;
    return s;
}

//扩容
static void expand(struct stack *s)
{
    if(s->size < s->capacity) return; //尚未满员，不必扩容
    s->elem = realloc(s->elem,(s->capacity<<=1)*sizeof(int));
}

void stack_push(struct stack *s, int e)
{
    expand(s);
    *(s->elem+s->size) = e;
    s->size++;
}

int stack_pop(struct stack *s)
{
    s->size--;
    return *(s->elem + s->size);
}
