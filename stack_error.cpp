#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack_error.h"
#include "stack.h"


const char* error_string[] = {
    "SUCCESS (error 0)",
    "NULL_PTR (error 1)",
    "OUT_OF_MEMORY (error 2)",
    "STACK_OVERFLOW (error 3)",
    "STACK_UNDERFLOW (error 4)",
    "POISON_CORRUPTED (error 5)",
    "CANARY_CORRUPTED (error 6)"};



Stack_err_t stackAssert(Stack_t* stack)
{
    Stack_err_t error_code = stackErr(stack);

    if (error_code != NULL_PTR && error_code != SUCCESS) {
        stackDump(stack, error_code);
        abort();
    }

    return error_code;
}


Stack_err_t stackErr(Stack_t* stack)
{
    if (stack == NULL || stack->data == NULL)
        return NULL_PTR;
    if (stack->data[0] != LEFT_CANARY ||
        stack->data[stack->capacity + 1] != RIGHT_CANARY)
        return CANARY_CORRUPTED;
    if (stack->size > stack->capacity)
        return STACK_OVERFLOW;
#ifdef DEBUG
    for (size_t index = stack->size + 1; index < stack->capacity + 1; index++)
        if (stack->data[index] != POISON)
            return POISON_CORRUPTED;
#endif 
    return SUCCESS;
}


void stackDump(Stack_t* stack, Stack_err_t err)
{
    if (stack == NULL) {
        printf("Stack [NULL POINTER], (%s)\n", error_string[err]);
        return;
    }

#ifdef DEBUG
    printf("Stack '%s' [%p] (%s)\n", 
            stack->debug_info.variable_name, stack, error_string[err]);
    printf("Created in %s() at %s:%d\n\n", stack->debug_info.function_name,
            stack->debug_info.file_name, stack->debug_info.line);
#else
    printf("Stack [%p] (%s)\n", stack, error_string[err]);
#endif
    printf("size = %zu\n", stack->size);
    printf("capacity = %zu\n\n", stack->capacity);

    if (stack->data == NULL) {
        printf("data[NULL POINTER]\n");
        return;
    }

    if (stack->data[0] == LEFT_CANARY)
        printf("LEFT_CANARY OK: 0x%X\n", (unsigned int)stack->data[0]);
    else
        printf("LEFT_CANARY NOT OK: 0x%X (expected 0x%X)\n",
                (unsigned int)stack->data[0], (unsigned int)LEFT_CANARY);
        
    if (stack->data[stack->capacity + 1] == RIGHT_CANARY)
        printf("RIGHT_CANARY OK: 0x%X\n", (unsigned int)stack->data[stack->capacity + 1]);
    else
        printf("RIGHT_CANARY NOT OK: 0x%X (expected 0x%X)\n", 
                (unsigned int)stack->data[stack->capacity + 1], (unsigned int)RIGHT_CANARY);

    printf("data[%p]\n", stack->data);
#ifdef DEBUG 
    printf("{\n");
    size_t index = 0;
    for (index = 1; index < stack->size + 1; index++)
        printf("\t*[%zu] = " SPEC"\n", index - 1, stack->data[index]);

    for (; index < stack->capacity + 1; index++) {
        if (stack->data[index] == POISON)
            printf("\t [%zu] = POISON\n", index - 1);
        else
            printf("\t [%zu] = CORRUPTED (not POISON)\n", index - 1);
    }
    printf("}\n");
#endif
}
