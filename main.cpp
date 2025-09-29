#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


int main()
{
    INIT_STACK(stack);

    stackCtor(&stack, START_CAPACITY);

    stack.data[0] = 5;
    stackPush(&stack, 10);

    stackDtor(&stack);

    return 0;
}


