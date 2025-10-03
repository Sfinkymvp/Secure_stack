#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"
#ifdef HASH
#include "stack_hash.h"
#endif // HASH


static StackError stackExpand(Stack_t* stack)
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
        return OUT_OF_MEMORY;
    }
    
    stack->data = (Element_t*)temp;
    stack->capacity *= 2;
#ifdef CANARY
    stack->data[stack->capacity + SHIFT] = RIGHT_CANARY;
#endif // CANARY
#ifdef POISON
    for (size_t index = stack->capacity / 2 + SHIFT;
         index < stack->capacity + SHIFT; index++)
        stack->data[index] = POISON_VALUE;
#endif // POISON
#ifdef HASH
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT

    return SUCCESS;
}


static StackError stackShrink(Stack_t* stack)
{
    StackError error_code = stackAssert(stack);
    if (error_code != SUCCESS)
        return error_code;

    size_t new_capacity = stack->capacity / 2;
#ifdef CANARY
    new_capacity += 2;
#endif // CANARY

    void* temp = realloc(stack->data, new_capacity * sizeof(Element_t));
    if (temp == NULL) {
        return OUT_OF_MEMORY;
    }

    stack->data = (Element_t*)temp;
    stack->capacity /= 2;
#ifdef CANARY
    stack->data[stack->capacity + SHIFT] = RIGHT_CANARY;
#endif // CANARY
#ifdef HASH
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT

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
    stack->data[stack->capacity + SHIFT] = RIGHT_CANARY;
#endif // CANARY
#ifdef POISON
    for (size_t index = SHIFT; index < stack->capacity + SHIFT; index++)
        stack->data[index] = POISON_VALUE;
#endif // POISON
#ifdef HASH
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT

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

    stack->data[stack->size++ + SHIFT] = value;
#ifdef HASH 
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT

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

    *value = stack->data[--stack->size + SHIFT];
#ifdef POISON
    stack->data[stack->size + SHIFT] = POISON_VALUE;
#endif // POISON
#ifdef HASH
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT

    if (stack->size <= stack->capacity / 4 &&
        stack->capacity > START_CAPACITY)
        stackShrink(stack);

    return stackAssert(stack);
}
