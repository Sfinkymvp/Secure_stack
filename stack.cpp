#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"


static StackError stackExpand(Stack_t* stack)
{
    StackError error_code = stackAssert(stack);
    if (error_code != SUCCESS)
        return error_code;

    void* temp = realloc(stack->data, (stack->capacity * 2 + 2) * sizeof(Element_t));
    if (temp == NULL) {
        free(stack->data);
        return OUT_OF_MEMORY;
    }
    
    stack->data = (Element_t*)temp;
    stack->capacity *= 2;
    stack->data[stack->capacity + 1] = RIGHT_CANARY;
#ifdef DEBUG
    for (size_t index = stack->capacity / 2 + 1; index < stack->capacity + 1; index++)
        stack->data[index] = POISON;
#endif

    return SUCCESS;
}


StackError stackCtor(Stack_t* stack, size_t size)
{
    if (stack == NULL)
        return NULL_PTR;

    stack->data = (Element_t*)calloc(size + 2, sizeof(Element_t));
    if (stack->data == NULL)
        return OUT_OF_MEMORY;

    stack->capacity = size;
    stack->size = 0;
    stack->data[0] = LEFT_CANARY;
#ifdef DEBUG
    for (size_t index = 1; index < stack->capacity + 1; index++)
        stack->data[index] = POISON;
#endif
    stack->data[stack->capacity + 1] = RIGHT_CANARY;

    return stackErr(stack);
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

    stack->data[stack->size++ + 1] = value;
  
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

    *value = stack->data[--stack->size + 1];
#ifdef DEBUG
    stack->data[stack->size + 1] = POISON;
#endif

    return stackAssert(stack);
}
