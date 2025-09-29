#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


int main()
{
    INIT_STACK(stack);

    stackCtor(&stack, START_CAPACITY);

    if (stackPush(&stack, 10) != SUCCESS)
        return 1;
    
    for (size_t index = 0; index <= stack.capacity + 1; index++)
        stack.data[index] = 52;

    Element_t num = 0;
    if (stackPop(&stack, &num) != SUCCESS)
        return 1;


    printf(SPEC"\n", num);

    stackDtor(&stack);

    return 0;
}


