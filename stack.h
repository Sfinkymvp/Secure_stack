#ifndef _STACK_H_
#define _STACK_H_


#include "stack_data.h"
#include "stack_error.h"


#ifdef DEBUG
#define INIT(name) .debug_info = {#name, __func__, __FILE__, __LINE__}
#define INIT_STACK(name) Stack_t name = {INIT(name)}
#endif // DEBUG


StackError stackExpand(Stack_t* stack);


StackError stackCtor(Stack_t* stack, size_t start_capacity);


StackError stackDtor(Stack_t* stack);


StackError stackPush(Stack_t* stack, Element_t value);


StackError stackPop(Stack_t* stack, Element_t* value);


#endif // _STACK_H_
