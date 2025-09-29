#ifndef _STACK_DATA_H_
#define _STACK_DATA_H_


const int START_CAPACITY = 10;


typedef int Element_t;
#define SPEC "%d"

#ifdef DEBUG
const Element_t POISON = 0x1DF1E1D;
#endif

const Element_t LEFT_CANARY = 0xFF1C1A1;
const Element_t RIGHT_CANARY = 0xFF51DE5;


typedef enum {
    SUCCESS = 0,
    NULL_PTR,
    OUT_OF_MEMORY,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    POISON_CORRUPTED,
    CANARY_CORRUPTED
} StackError;


#ifdef DEBUG
typedef struct {
    const char* variable_name;
    const char* function_name;
    const char* file_name;
    int line;
} StackDebugInfo;
#endif


typedef struct {
    Element_t* data;
    size_t size;
    size_t capacity;
#ifdef DEBUG
    StackDebugInfo debug_info;
#endif
} Stack_t;


#endif
