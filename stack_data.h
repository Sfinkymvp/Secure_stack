#ifndef _STACK_DATA_H_
#define _STACK_DATA_H_


const int START_CAPACITY = 10;


typedef int Element_t;
#define SPEC "%d"


#define GR "\x1b[32m"
#define DF "\x1b[31m"


#ifdef POISON
const Element_t POISON_VALUE = 0x1DF1E1D;
#endif // POISON
#ifdef CANARY
const Element_t LEFT_CANARY = 0xFF1C1A1;
const Element_t RIGHT_CANARY = 0xFF51DE5;
#endif // CANARY


typedef enum {
    SUCCESS = 0,
    NULL_PTR,
    OUT_OF_MEMORY,
    STACK_UNDERFLOW,
    STACK_OVERFLOW,
    CANARY_CORRUPTED,
    POISON_CORRUPTED,
    HASH_CORRUPTED
} StackError;


#ifdef DEBUG
typedef struct {
    const char* variable_name;
    const char* function_name;
    const char* file_name;
    int line;
} StackDebugInfo;
#endif // DEBUG


typedef struct {
    Element_t* data;
    size_t size;
    size_t capacity;
#ifdef DEBUG
    StackDebugInfo debug_info;
#endif // DEBUG
#ifdef HASH
    size_t hash;
#endif // HASH
} Stack_t;


#endif // _STACK_DATA_H_
