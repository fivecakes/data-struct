#ifndef stack_h
#define stack_h
#include "vector.h"

typedef Vector Stack;
static Stack initStack();
static void push(Stack *S, int e);

static int pop(Stack *S);
#endif /* stack_h */
