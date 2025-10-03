#include <stdio.h>
#include <string.h>

#include "stack_tests.h"
#include "stack.h"


void testNormal()
{
    printf(GR "testNormal():" DF"\n");

    INIT_STACK(stack_normal);

    stackCtor(&stack_normal, 5);

    stackPush(&stack_normal, 37);
    stackPush(&stack_normal, 49);

    Element_t value = 0;
    StackError error_code = stackPop(&stack_normal, &value);
    printf("Test success: %s\n", ErrorString[error_code]);
    
    stackDtor(&stack_normal);
}


void testUnderflow()
{
    printf(GR "\n\n\ntestUnderflow():" DF"\n");

    INIT_STACK(stack_underflow);

    stackCtor(&stack_underflow, 5);

    Element_t value = 0;
    StackError error_code = stackPop(&stack_underflow, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_underflow);
}


#ifdef CANARY
void testStackCanaryCorruption()
{
    printf(GR "\n\n\ntestStackCanaryCorruption():" DF"\n");

    INIT_STACK(stack_canary);

    stackCtor(&stack_canary, 5);

    stackPush(&stack_canary, 523);

    stack_canary.data[-1] = 100500;
    stack_canary.data[stack_canary.capacity] = 112358;
    
    StackError error_code = stackPush(&stack_canary, 52);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_canary);
}
#endif // CANARY


#ifdef POISON
void testPoisonCorruption()
{
    printf(GR "\n\n\ntestPoisonCorruption():" DF"\n");

    INIT_STACK(stack_poison);

    stackCtor(&stack_poison, 5);

    stackPush(&stack_poison, 42);
    stack_poison.data[stack_poison.size] = 111;

    Element_t value = 0;
    StackError error_code = stackPop(&stack_poison, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_poison); 
}
#endif // POISON


#ifdef HASH
void testStackHashCorruption()
{
    printf(GR "\n\n\ntestStackHashCorruption():" DF"\n");

    INIT_STACK(stack_hash);

    stackCtor(&stack_hash, 5);
    
    stackPush(&stack_hash, 5);
    stackPush(&stack_hash, 8);
    stack_hash.data[0] = 888;
    stack_hash.data[1] = 555;

    Element_t value = 0;
    StackError error_code = stackPop(&stack_hash, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_hash);
}
#endif // HASH


#ifdef STRUCT_PROTECT
void testStructCanaryCorruption()
{
    printf(GR "\n\n\ntestStructCanaryCorruption():" DF"\n");

    INIT_STACK(stack_scanary);

    stackCtor(&stack_scanary, 5);

    stackPush(&stack_scanary, 55);

    memset(&stack_scanary, 0, sizeof(size_t));

    Element_t value = 0;
    StackError error_code = stackPop(&stack_scanary, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_scanary);
}


void testStructHashCorruption()
{
    printf(GR "\n\n\ntestStructHashCorruption():" DF"\n");

    INIT_STACK(stack_shash);

    stackCtor(&stack_shash, 5);

    stackPush(&stack_shash, 32);

    stack_shash.size = 100000;

    Element_t value = 0;
    StackError error_code = stackPop(&stack_shash, &value);
    printf("Test error: %s\n", ErrorString[error_code]);

    stackDtor(&stack_shash);
}


#endif // STRUCT_PROTECT
