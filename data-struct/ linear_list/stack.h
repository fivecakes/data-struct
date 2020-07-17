#ifndef stack_h
#define stack_h
#include "common.h"
struct Stack{
    int *elem;
    int size;
    int capacity;
};


struct Stack stack_init(void);
void stack_push(struct Stack *S, int e);

int stack_pop(struct Stack *S);
#endif /* stack_h */
