#ifndef stack_h
#define stack_h

struct Stack{
    int *elem;
    int size;
    int capacity;
};

typedef struct Stack Stack;

static Stack initStack(void);
static void push(Stack *S, int e);

static int pop(Stack *S);
#endif /* stack_h */
