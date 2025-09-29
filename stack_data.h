#ifndef _STACK_DATA_H_
#define _STACK_DATA_H_


const int START_CAPACITY = 10;


typedef int element_t;
#define SPEC "%d"

#ifdef DEBUG
const element_t POISON = 0x1DF1E1D;
#endif

const element_t LEFT_CANARY = 0xFF1C1A1;
const element_t RIGHT_CANARY = 0xFF51DE5;


typedef enum {
    SUCCESS = 0,
    NULL_PTR,
    OUT_OF_MEMORY,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    POISON_CORRUPTED,
    CANARY_CORRUPTED
} Stack_err_t;


#ifdef DEBUG
typedef struct {
    const char* variable_name;
    const char* function_name;
    const char* file_name;
    int line;
} StackDebugInfo;
#endif


typedef struct {
    element_t* data;
    size_t size;
    size_t capacity;
#ifdef DEBUG
    StackDebugInfo debug_info;
#endif
} Stack_t;


#endif
