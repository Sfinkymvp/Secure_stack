#include <stdio.h>

#include "stack_tests.h"
#include "stack.h"


#ifdef DEBUG
void testNormal()
{
    printf("\n\n\ntestNormal():\n");

    INIT_STACK(stack_normal);

    stackCtor(&stack_normal, 2);

    stackPush(&stack_normal, 37);
    stackPush(&stack_normal, 49);

    Element_t value = 0;
    StackError error_code = stackPop(&stack_normal, &value);
    printf("Test success: %s\n", ErrorString[error_code]);
    
    stackDtor(&stack_normal);
}


void testCanaryCorruption()
{
    printf("\n\n\ntestCanaryCorruption():\n");

    INIT_STACK(stack_canary);

    stackCtor(&stack_canary, 2);
    stack_canary.data[0] = 100500;
    stack_canary.data[stack_canary.capacity + 1] = 112358;

    StackError error_code = stackPush(&stack_canary, 52);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_canary);
}


void testPoisonCorruption()
{
    printf("\n\n\ntestPoisonCorruption():\n");

    INIT_STACK(stack_poison);

    stackCtor(&stack_poison, 2);

    stackPush(&stack_poison, 42);
    stack_poison.data[stack_poison.size + 1] = 111;

    Element_t value = 0;
    StackError error_code = stackPop(&stack_poison, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_poison); 
}


void testHashCorruption()
{
    printf("\n\n\ntestHashCorruption():\n");

    INIT_STACK(stack_hash);

    stackCtor(&stack_hash, 2);
    
    stackPush(&stack_hash, 5);
    stackPush(&stack_hash, 8);
    stack_hash.data[1] = 888;
    stack_hash.data[2] = 555;

    Element_t value = 0;
    StackError error_code = stackPop(&stack_hash, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_hash);
}


void testUnderflow()
{
    printf("\n\n\ntestUnderflow():\n");

    INIT_STACK(stack_underflow);

    stackCtor(&stack_underflow, 1);

    Element_t value = 0;
    StackError error_code = stackPop(&stack_underflow, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_underflow);
}
#endif
