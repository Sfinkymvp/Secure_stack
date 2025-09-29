#ifndef _STACK_H_
#define _STACK_H_


#include "stack_data.h"
#include "stack_error.h"


#ifdef DEBUG
#define INIT(name) .debug_info = {#name, __func__, __FILE__, __LINE__}
#define INIT_STACK(name) Stack_t name = {INIT(name)}
#else
#define INIT_STACK(name) Stack_t name = {}
#endif


StackError stackCtor(Stack_t* stack, size_t size);


StackError stackDtor(Stack_t* stack);


StackError stackPush(Stack_t* stack, Element_t value);


StackError stackPop(Stack_t* stack, Element_t* element);


#endif
