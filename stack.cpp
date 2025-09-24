#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


const char* stack_err_str[] = {
    "SUCCESS (Err 0)",
    "NULL_PTR (Err 1)",
    "OUT_OF_MEMORY (Err 2)",
    "STACK_OVERFLOW (Err 3)",
    "STACK_UNDERFLOW (Err 4)"};


stack_err_t stack_err(Stack_t* stack)
{
    if (stack == NULL || stack->data == NULL)
        return NULL_PTR;
    if (stack->size > stack->capacity)
        return STACK_OVERFLOW;
    if (stack->size == 0)
        return STACK_UNDERFLOW;

    return SUCCESS;
}


void stack_dump(Stack_t* stack, stack_err_t err)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

    printf("Stack '%s' [%p] (%s)\n", 
            stack->var_info.variable_name, stack, stack_err_str[err]);
    printf("Created in %s() at %s:%d\n\n", stack->var_info.function_name,
            stack->var_info.file_name, stack->var_info.line);
    printf("size = %zu\n", stack->size);
    printf("capacity = %zu\n\n", stack->capacity);
    printf("data[%p]\n", stack->data);
    printf("{\n");

    size_t index = 0;

    for (; index < stack->size; index++)
        printf("\t*[%zu] = " SPEC"\n", index, stack->data[index]);

    for (; index < stack->capacity; index++)
        printf("\t [%zu] = " SPEC"\n", index, stack->data[index]);

    printf("}\n");
}


stack_err_t stack_ctor(Stack_t* stack, size_t size)
{
    if (stack == NULL)
        return NULL_PTR;

    stack->data = (element_t*)calloc(size, sizeof(element_t));

    if (stack->data == NULL)
        return OUT_OF_MEMORY;
   
    stack->capacity = size;
    return SUCCESS;
}


void stack_dtor(Stack_t* stack)
{
    assert(stack != NULL);

    free(stack->data);
}


stack_err_t stack_push(Stack_t* stack, element_t value)
{
    assert(stack != NULL);
    assert(stack->data != NULL);


    stack->data[stack->size++] = value;

    stack_dump(stack, SUCCESS);

    return SUCCESS;
}


stack_err_t stack_pop(Stack_t* stack, element_t* element)
{
    if (element == NULL)
        return NULL_PTR;

    assert(stack != NULL);
    assert(stack->data != NULL);

    if (!stack_err(stack))
        return NULL_PTR;

    *element = stack->data[--stack->size];

    if (!stack_err(stack))
        return NULL_PTR;

    return SUCCESS;
}
