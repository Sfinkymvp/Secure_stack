#include <stdio.h>
#include <assert.h>

#include "stack_hash.h"
#include "stack_data.h"


size_t djb2(const unsigned char* data, size_t size)
{
    assert(data != NULL);

    size_t hash = 5381;
    for (size_t index = 0; index < size; index++)
        hash = ((hash << 5) + hash) + data[index];

    return hash;
}


bool checkStackHash(const Stack_t* stack)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

    return stack->hash ==
           djb2((const unsigned char*)(stack->data), sizeof(Element_t) * stack->size);
}


void calculateStackHash(Stack_t* stack)
{
    assert(stack != NULL);
    assert(stack->data != NULL);

    stack->hash = djb2((unsigned char*)(stack->data), sizeof(Element_t) * stack->size);
}


#ifdef STRUCT_PROTECT
bool checkStructHash(const Stack_t* stack)
{
    assert(stack != NULL);

    return stack->struct_hash ==
           djb2((const unsigned char*)stack + sizeof(size_t), sizeof(Stack_t) - sizeof(size_t) * 3);
}


void calculateStructHash(Stack_t* stack)
{
    assert(stack != NULL);

    stack->struct_hash = djb2((unsigned char*)stack + sizeof(size_t), sizeof(Stack_t) - sizeof(size_t) * 3);
}
#endif // STRUCT_PROTECT


void updateHashes(Stack_t* stack)
{
    assert(stack != NULL);

#ifdef HASH
    calculateStackHash(stack);
#endif // HASH
#ifdef STRUCT_PROTECT
    calculateStructHash(stack);
#endif // STRUCT_PROTECT
}
