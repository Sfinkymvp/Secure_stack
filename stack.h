#ifndef _STACK_H_
#define _STACK_H_


const int START_CAPACITY = 10;


typedef int element_t;
#define SPEC "%d"


#define INIT(name) .var_info = {#name, __func__, __FILE__, __LINE__}
#define INIT_STACK(name) Stack_t name = {INIT(name)}


typedef enum {
    SUCCESS = 0,
    NULL_PTR,
    OUT_OF_MEMORY,
    STACK_OVERFLOW,
    STACK_UNDERFLOW
} stack_err_t;


typedef struct {
    const char* variable_name;
    const char* function_name;
    const char* file_name;
    int line;
} Stack_creation_info;


typedef struct {
    element_t* data;
    size_t size;
    size_t capacity;
    Stack_creation_info var_info;
} Stack_t;


stack_err_t stack_ctor(Stack_t* stack, size_t size);


stack_err_t stack_dtor(Stack_t* stack);


stack_err_t stack_push(Stack_t* stack, element_t value);


stack_err_t stack_pop(Stack_t* stack, element_t* element);


#endif
