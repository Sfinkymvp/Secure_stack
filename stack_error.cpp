#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack_error.h"
#include "stack.h"


const char* ErrorString[] = {
    "SUCCESS (error 0)",
    "NULL_PTR (error 1)",
    "OUT_OF_MEMORY (error 2)",
    "STACK_OVERFLOW (error 3)",
    "STACK_UNDERFLOW (error 4)",
    "POISON_CORRUPTED (error 5)",
    "CANARY_CORRUPTED (error 6)"};



StackError _stackAssert(Stack_t* stack,
                       const char* function,
                       const char* file,
                       int line)
{
    StackError error_code = stackErr(stack);

    if (error_code != SUCCESS) {
#ifdef DEBUG
        fprintf(stderr, "StackAssert triggered in %s (%s:%d)\n",
                function, file, line);
#endif
        if (error_code != NULL_PTR) {
            stackDump(stack, error_code);
            stackDtor(stack);
            abort();
        }
    }

    return error_code;
}


StackError stackErr(Stack_t* stack)
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


void stackDump(Stack_t* stack, StackError error_code)
{
    if (stack == NULL) {
        fprintf(stderr, "Stack [NULL POINTER], (%s)\n", ErrorString[error_code]);
        return;
    }

#ifdef DEBUG
    fprintf(stderr, "Stack '%s' [%p] (%s)\n", 
            stack->debug_info.variable_name, stack, ErrorString[error_code]);
    fprintf(stderr, "Created in %s() at %s:%d\n\n", stack->debug_info.function_name,
            stack->debug_info.file_name, stack->debug_info.line);
#else
    fprintf(stderr, "Stack [%p] (%s)\n", stack, ErrorString[error_code]);
#endif
    fprintf(stderr, "size = %zu\n", stack->size);
    fprintf(stderr, "capacity = %zu\n\n", stack->capacity);

    if (stack->data == NULL) {
        fprintf(stderr, "data[NULL POINTER]\n");
        return;
    }

    if (stack->data[0] == LEFT_CANARY)
        fprintf(stderr, "LEFT_CANARY OK: 0x%X\n", (unsigned int)stack->data[0]);
    else
        fprintf(stderr, "LEFT_CANARY NOT OK: 0x%X (expected 0x%X)\n",
                (unsigned int)stack->data[0], (unsigned int)LEFT_CANARY);
        
    if (stack->data[stack->capacity + 1] == RIGHT_CANARY)
        fprintf(stderr, "RIGHT_CANARY OK: 0x%X\n", (unsigned int)stack->data[stack->capacity + 1]);
    else
        fprintf(stderr, "RIGHT_CANARY NOT OK: 0x%X (expected 0x%X)\n", 
                (unsigned int)stack->data[stack->capacity + 1], (unsigned int)RIGHT_CANARY);

    fprintf(stderr, "data[%p]\n", stack->data);
#ifdef DEBUG 
    fprintf(stderr, "{\n");
    size_t index = 0;
    for (index = 1; index < stack->size + 2; index++)
        fprintf(stderr, "\t*[%zu] = " SPEC"\n", index - 1, stack->data[index]);

    for (; index < stack->capacity + 1; index++) {
        if (stack->data[index] == POISON)
            fprintf(stderr, "\t [%zu] = POISON\n", index - 1);
        else
            fprintf(stderr, "\t [%zu] = CORRUPTED (not POISON)\n", index - 1);
    }
    fprintf(stderr, "}\n");
#endif
}
