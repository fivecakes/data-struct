#ifndef stack_h
#define stack_h
#include "../common.h"
struct stack{
    int *elem;
    int size;
    int capacity;
};


struct stack stack_init(void);
void stack_push(struct stack *S, int e);

int stack_pop(struct stack *S);
#endif /* stack_h */
