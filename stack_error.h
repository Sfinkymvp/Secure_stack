#ifndef _STACK_ERROR_H_
#define _STACK_ERROR_H_


#include "stack.h"


extern const char* stack_err_str[];


stack_err_t stack_err(Stack_t* stack);


void stack_dump(Stack_t* stack, stack_err_t err);


#endif
