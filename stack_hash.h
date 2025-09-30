#ifndef _STACK_HASH_H_
#define _STACK_HASH_H_


#include <stdio.h>

#include "stack_data.h"

#ifdef DEBUG
size_t djb2(const unsigned char* data, size_t size);


bool checkHash(const Stack_t* stack);


void calculateHash(Stack_t* stack);
#endif


#endif
