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


Stack_err_t stackCtor(Stack_t* stack, size_t size);


Stack_err_t stackDtor(Stack_t* stack);


Stack_err_t stackPush(Stack_t* stack, element_t value);


Stack_err_t stackPop(Stack_t* stack, element_t* element);


#endif
