#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


int main()
{
    INIT_STACK(stack);

    stack_ctor(&stack, START_CAPACITY);

    stack_push(&stack, 10);

    stack_push(&stack, 20);

    stack_push(&stack, 30);
    
    element_t element = 0;
  
    stack_dtor(&stack);

    return 0;
}


