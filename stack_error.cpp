#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack_error.h"
#include "stack.h"
#ifdef DEBUG
#include "stack_hash.h"
#endif


const char* ErrorString[] = {
    "SUCCESS (error 0)",
    "NULL_PTR (error 1)",
    "OUT_OF_MEMORY (error 2)",
    "STACK_UNDERFLOW (error 3)",
    "STACK_OVERFLOW (error 4)",
    "CANARY_CORRUPTED (error 5)",
    "POISON_CORRUPTED (error 6)",
    "HASH_CORRUPTED (error 7)"};


#ifdef DEBUG
StackError _stackAssert(const Stack_t* stack,
                       const char* function,
                       const char* file,
                       int line)
{
    StackError error_code = stackVerify(stack);

    if (error_code != SUCCESS) {
        fprintf(stderr, "StackAssert triggered in %s (%s:%d)\n",
                function, file, line);
        stackDump(stack, error_code);
#ifdef HARD
        if (stack != NULL)
            stackDtor(stack);
        abort();
#endif // HARD
    }
    return error_code;
}
#else
StackError _stackAssert(const Stack_t* stack)
{
    StackError error_code = stackVerify(stack);

    if (error_code != SUCCESS) {
        stackDump(stack, error_code);
#ifdef HARD
        if (stack != NULL)
            stackDtor(stack);
        abort();
#endif // HARD
    }
    return error_code;
}
#endif // DEBUG


StackError stackVerify(const Stack_t* stack)
{
    if (stack == NULL || stack->data == NULL)
        return NULL_PTR;
    if (stack->size > stack->capacity)
        return STACK_OVERFLOW;
#ifdef CANARY
    if (stack->data[0] != LEFT_CANARY ||
        stack->data[stack->capacity + 1] != RIGHT_CANARY)
        return CANARY_CORRUPTED;
#endif // CANARY
#ifdef HASH
    if (!checkHash(stack))
        return HASH_CORRUPTED; 
#endif // HASH
#ifdef POISON
    size_t shift = 0;
    #ifdef CANARY
        shift = 1;
    #endif // CANARY IN POISON
    for (size_t index = stack->size + shift; index < stack->capacity + shift; index++)
        if (stack->data[index] != POISON_VALUE)
            return POISON_CORRUPTED;
#endif // POISON

    return SUCCESS;
}


void stackDump(const Stack_t* stack, StackError error_code)
{
    if (stack == NULL) {
        fprintf(stderr, "Stack [NULL POINTER], (%s)\n", ErrorString[error_code]);
        return;
    }

#ifdef DEBUG
    printDebugInfo(stack, error_code);
#else
    fprintf(stderr, "Stack [%p] (%s)\n", stack, ErrorString[error_code]);
#endif // DEBUG
    fprintf(stderr, "size = %zu\n", stack->size);
    fprintf(stderr, "capacity = %zu\n\n", stack->capacity);

    if (stack->data == NULL) {
        fprintf(stderr, "data[NULL POINTER]\n");
        return;
    }
#ifdef CANARY
    printCanaryState(stack);
#endif // CANARY

    fprintf(stderr, "data[%p]\n", stack->data);
#ifdef DEBUG 
    printStackData(stack);
#endif // DEBUG
}


#ifdef CANARY
void printCanaryState(const Stack_t* stack)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

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
}
#endif // CANARY


#ifdef DEBUG
void printDebugInfo(const Stack_t* stack, StackError error_code)
{
    fprintf(stderr, "Stack '%s' [%p] (%s)\n", 
            stack->debug_info.variable_name, stack, ErrorString[error_code]);
    fprintf(stderr, "Created in %s() at %s:%d\n\n", stack->debug_info.function_name,
            stack->debug_info.file_name, stack->debug_info.line);
}
#endif // DEBUG


#ifdef DEBUG
void printStackData(const Stack_t* stack)
{
    fprintf(stderr, "{\n");

#ifdef CANARY
    size_t canary_shift = 1;
#else
    size_t canary_shift = 0;
#endif // CANARY
    size_t index = 0;
    for (index = canary_shift; index < stack->size + canary_shift; index++)
        fprintf(stderr, "\t*[%zu] = " SPEC"\n", index - canary_shift, stack->data[index]);

#ifdef POISON
    for (; index < stack->capacity + canary_shift; index++) {
        if (stack->data[index] == POISON_VALUE)
            fprintf(stderr, "\t [%zu] = POISON\n", index - canary_shift);
        else
            fprintf(stderr, "\t [%zu] = CORRUPTED (not POISON)\n", index - canary_shift);
    }
#endif // POISON
    fprintf(stderr, "}\n");
}
#endif // DEBUG
