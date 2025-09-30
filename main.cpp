#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


int main()
{
    INIT_STACK(stack);

    stackCtor(&stack, START_CAPACITY);

    stackPush(&stack, 10);

    stack.data[0] = 52;

    Element_t num = 0;
    stackPop(&stack, &num);

    stackDtor(&stack);

    return 0;
}


