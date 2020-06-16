//
//  stack.h
//  data-struct
//
//  Created by book on 2020/6/16.
//  Copyright © 2020 book. All rights reserved.
//

#ifndef stack_h
#define stack_h
#include "vector.h"

typedef Vector Stack;
static Stack initStack();
static void push(Stack *S, int e);

static int pop(Stack *S);
#endif /* stack_h */
