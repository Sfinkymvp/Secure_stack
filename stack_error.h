#ifndef _STACK_ERROR_H_
#define _STACK_ERROR_H_


#include "stack_data.h"


extern const char* error_string[];


Stack_err_t stackAssert(Stack_t* stack);


Stack_err_t stackErr(Stack_t* stack);


void stackDump(Stack_t* stack, Stack_err_t err);


#endif
