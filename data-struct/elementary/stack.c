#include "stack.h"

Stack initStack()
{
    Stack S;
    S.elem = malloc(2* sizeof(int));
    S.capacity =2;
    S.size = 0;
    return S;
}

//扩容
static void expand(Stack *S)
{
    if(S->size < S->capacity) return; //尚未满员，不必扩容
    S->elem = realloc(S->elem,(S->capacity<<=1)*sizeof(int));
}

void push(Stack *S, int e)
{
    expand(S);
    *(S->elem+S->size) = e;
    S->size++;
}

int pop(Stack *S)
{
    S->size--;
    return *(S->elem + S->size);
}