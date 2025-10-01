#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"
#ifdef HASH
#include "stack_hash.h"
#endif // HASH


StackError stackExpand(Stack_t* stack)
{
    StackError error_code = stackAssert(stack);
    if (error_code != SUCCESS)
        return error_code;

    size_t new_capacity = stack->capacity * 2;
#ifdef CANARY
    new_capacity += 2;
#endif // CANARY

    void* temp = realloc(stack->data, new_capacity * sizeof(Element_t));
    if (temp == NULL) {
        free(stack->data);
        return OUT_OF_MEMORY;
    }
    
    stack->data = (Element_t*)temp;
    stack->capacity *= 2;
#ifdef CANARY
    stack->data[stack->capacity + 1] = RIGHT_CANARY;
#endif // CANARY
#ifdef POISON
    size_t shift = 0;
    #ifdef CANARY
        shift = 1;
    #endif // CANARY IN POISON
    for (size_t index = stack->capacity / 2 + shift;
         index < stack->capacity + shift; index++)
        stack->data[index] = POISON_VALUE;
#endif // POISON
#ifdef HASH
    calculateHash(stack);
#endif // HASH

    return SUCCESS;
}


StackError stackCtor(Stack_t* stack, size_t start_capacity)

{
    if (stack == NULL)
        return NULL_PTR;

    size_t canary_capacity = 0;
#ifdef CANARY
    canary_capacity = 2;
#endif // CANARY
    stack->data = (Element_t*)calloc(start_capacity + canary_capacity, sizeof(Element_t));
    if (stack->data == NULL)
        return OUT_OF_MEMORY;

    stack->capacity = start_capacity;
    stack->size = 0;
#ifdef CANARY
    stack->data[0] = LEFT_CANARY;
    stack->data[stack->capacity + 1] = RIGHT_CANARY;
#endif // CANARY
#ifdef POISON
    size_t shift = 0;
    #ifdef CANARY
        shift = 1;
    #endif // CANARY IN POISON

    for (size_t index = shift; index < stack->capacity + shift; index++)
        stack->data[index] = POISON_VALUE;
#endif // POISON
#ifdef HASH
    calculateHash(stack);
#endif // HASH

    return SUCCESS;
}


StackError stackDtor(Stack_t* stack)
{
    if (stack == NULL)
        return NULL_PTR;

    free(stack->data);
    stack->data = NULL;

    return SUCCESS;
}


StackError stackPush(Stack_t* stack, Element_t value)
{
    StackError error_code = stackAssert(stack);

    if (error_code != SUCCESS) 
        return error_code; 

    if (stack->size == stack->capacity) {
        error_code = stackExpand(stack);
        if (error_code != SUCCESS)
            return error_code;
    }

#ifdef CANARY
    stack->data[stack->size++ + 1] = value;
#else
    stack->data[stack->size++] = value;
#endif // CANARY
#ifdef HASH 
    calculateHash(stack);
#endif // HASH
  
    return stackAssert(stack);
}


StackError stackPop(Stack_t* stack, Element_t* value)
{
    if (value == NULL)
        return NULL_PTR;

    StackError error_code = stackAssert(stack);
    if (error_code != SUCCESS)
        return error_code;
    if (stack->size == 0)
        return STACK_UNDERFLOW;

#ifdef CANARY
    *value = stack->data[--stack->size + 1];
#else
    *value = stack->data[--stack->size];
#endif // CANARY
#ifdef POISON
    #ifdef CANARY
        stack->data[stack->size + 1] = POISON_VALUE;
    #else
        stack->data[stack->size] = POISON_VALUE;
    #endif // CANARY IN POISON
#endif // POISON
#ifdef HASH
    calculateHash(stack);
#endif // HASH

    return stackAssert(stack);
}
