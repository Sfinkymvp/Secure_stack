#include <stdio.h>
#include <assert.h>

#include "stack_hash.h"
#include "stack_data.h"


#ifdef DEBUG
size_t djb2(const unsigned char* data, size_t size)
{
    assert(data != NULL);

    size_t hash = 5381;
    for (size_t index = 0; index < size; index++)
        hash = ((hash << 5) + hash) + data[index];

    return hash;
}


bool checkHash(const Stack_t* stack)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

    return stack->hash == djb2((unsigned char*)stack->data, sizeof(Element_t) * (stack->size + 1));
}


void calculateHash(Stack_t* stack)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

    stack->hash = djb2((unsigned char*)stack->data, sizeof(Element_t) * (stack->size + 1));
}
#endif

