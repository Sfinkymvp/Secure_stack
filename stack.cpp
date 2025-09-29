#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"


static Stack_err_t stackExpand(Stack_t* stack)
{
    Stack_err_t error_code = stackErr(stack);
    if (error_code != SUCCESS)
        return error_code;

    void* temp = realloc(stack->data, (stack->capacity * 2 + 2) * sizeof(*stack->data));
    if (temp == NULL) {
        free(stack->data);
        return OUT_OF_MEMORY;
    }
    
    stack->data = (element_t*)temp;
    stack->capacity *= 2;
    stack->data[stack->capacity + 1] = RIGHT_CANARY;

#ifdef DEBUG
    for (size_t index = stack->capacity / 2; index < stack->capacity + 1; index++)
        stack->data[index] = POISON;
#endif

    return SUCCESS;
}


Stack_err_t stackCtor(Stack_t* stack, size_t size)
{
    if (stack == NULL)
        return NULL_PTR;

    stack->data = (element_t*)calloc(size + 2, sizeof(element_t));
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


Stack_err_t stackDtor(Stack_t* stack)
{
    Stack_err_t error_code = stackErr(stack);
    if (error_code == NULL_PTR)
        return error_code;

    free(stack->data);
    stack->data = NULL;

    return error_code;
}


Stack_err_t stackPush(Stack_t* stack, element_t value)
{
    Stack_err_t error_code = stackErr(stack);
    if (error_code != SUCCESS) {
        stackDump(stack, error_code);
        return error_code; 
    }

    if (stack->size == stack->capacity) {
        error_code = stackExpand(stack);
        if (error_code != SUCCESS)
            return error_code;
    }

    stack->data[stack->size++ + 1] = value;
  
    return stackErr(stack);
}


Stack_err_t stackPop(Stack_t* stack, element_t* element)
{
    if (element == NULL)
        return NULL_PTR;

    Stack_err_t error_code = stackErr(stack);
    if (error_code != SUCCESS)
        return error_code;
    if (stack->size == 0)
        return STACK_UNDERFLOW;
        
    *element = stack->data[--stack->size + 1];

    return stackErr(stack);
}
