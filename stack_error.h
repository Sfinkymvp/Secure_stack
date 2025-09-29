#ifndef _STACK_ERROR_H_
#define _STACK_ERROR_H_


#include "stack_data.h"


#define stackAssert(stack) _stackAssert(stack, __func__, __FILE__, __LINE__)


extern const char* ErrorString[];


StackError _stackAssert(Stack_t* stack,
                       const char* function,
                       const char* file,
                       int line);


StackError stackErr(Stack_t* stack);


void stackDump(Stack_t* stack, StackError error_code);


#endif
