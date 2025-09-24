#include <stdio.h>
#include <assert.h>

#include "stack_error.h"
#include "stack.h"


const char* stack_err_str[] = {
    "SUCCESS (Error 0)",
    "NULL_PTR (Error 1)",
    "OUT_OF_MEMORY (Error 2)",
    "STACK_OVERFLOW (Error 3)"};


stack_err_t stack_err(Stack_t* stack)
{
    if (stack == NULL || stack->data == NULL)
        return NULL_PTR;
    if (stack->size > stack->capacity) {
        stack_dump(stack, STACK_OVERFLOW);
        return STACK_OVERFLOW;
    }

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
