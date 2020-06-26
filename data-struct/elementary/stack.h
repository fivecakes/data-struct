#ifndef stack_h
#define stack_h
#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int *elem;
    int size;
    int capacity;
};

typedef struct Stack Stack;

Stack stack_init(void);
void stack_push(Stack *S, int e);

int stack_pop(Stack *S);
#endif /* stack_h */
