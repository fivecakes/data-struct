#ifndef stack_h
#define stack_h

struct Stack{
    int *elem;
    int size;
    int capacity;
};

typedef struct Stack Stack;

Stack initStack(void);
void push(Stack *S, int e);

int pop(Stack *S);
#endif /* stack_h */
