#include "stack.h"

struct Stack stack_init()
{
    struct Stack S;
    S.elem = malloc(2* sizeof(int));
    S.capacity =2;
    S.size = 0;
    return S;
}

//扩容
static void expand(struct Stack *S)
{
    if(S->size < S->capacity) return; //尚未满员，不必扩容
    S->elem = realloc(S->elem,(S->capacity<<=1)*sizeof(int));
}

void stack_push(struct Stack *S, int e)
{
    expand(S);
    *(S->elem+S->size) = e;
    S->size++;
}

int stack_pop(struct Stack *S)
{
    S->size--;
    return *(S->elem + S->size);
}
