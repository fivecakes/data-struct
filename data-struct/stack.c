#include "stack.h"

static Stack initStack()
{
    return initVector();
}

static void push(Stack *S, int e)
{
    insertBottom(S, e);
}

static int pop(Stack *S)
{
    S->size--;
    return *(S->elem + S->size);
}
