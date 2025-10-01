#ifndef _STACK_ERROR_H_
#define _STACK_ERROR_H_


#include "stack_data.h"


#ifdef DEBUG
#define stackAssert(stack) _stackAssert(stack, __func__, __FILE__, __LINE__)
#else
#define stackAssert(stack) _stackAssert(stack)
#endif // DEBUG


extern const char* ErrorString[];


#ifdef DEBUG
StackError _stackAssert(const Stack_t* stack,
                        const char* function,
                        const char* file,
                        int line);
#else
StackError _stackAssert(const Stack_t* stack);
#endif // DEBUG


StackError stackVerify(const Stack_t* stack);


void stackDump(const Stack_t* stack, StackError error_code);


#ifdef CANARY
void printCanaryState(const Stack_t* stack);
#endif // CANARY


#ifdef DEBUG
void printDebugInfo(const Stack_t* stack, StackError error_code);


void printStackData(const Stack_t* stack);
#endif // DEBUG


#endif // _STACK_ERROR_H_
