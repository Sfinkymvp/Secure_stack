#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"


stack_err_t stack_ctor(Stack_t* stack, size_t size)
{
    if (stack == NULL)
        return NULL_PTR;

    stack->data = (element_t*)calloc(size, sizeof(element_t));
    if (stack->data == NULL)
        return OUT_OF_MEMORY;
   
    stack->capacity = size;

    return stack_err(stack);
}


stack_err_t stack_dtor(Stack_t* stack)
{
    stack_err_t error_code = stack_err(stack);
    
    if (error_code == NULL_PTR)
        return error_code;

    free(stack->data);

    return error_code;
}


stack_err_t stack_push(Stack_t* stack, element_t value)
{
    stack_err_t error_code = stack_err(stack);
    if (error_code != SUCCESS)
        return error_code; 

    stack->data[stack->size++] = value;
  
    stack_dump(stack, SUCCESS);

    return stack_err(stack);
}


stack_err_t stack_pop(Stack_t* stack, element_t* element)
{
    if (element == NULL)
        return NULL_PTR;

    stack_err_t error_code = stack_err(stack);
    if (error_code != SUCCESS)
        return error_code;

    *element = stack->data[--stack->size];

    return stack_err(stack);
}
