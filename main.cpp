#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#ifdef DEBUG
#include "stack_tests.h"
#endif // DEBUG


int main()
{
#ifdef DEBUG
    testNormal();

    testUnderflow();

#ifdef CANARY
    testStackCanaryCorruption();
#endif // CANARY IN DEBUG

#ifdef POISON
    testPoisonCorruption();
#endif // POISON IN DEBUG

#ifdef HASH
    testStackHashCorruption();
#endif // HASH IN DEBUG

#ifdef STRUCT_PROTECT
    testStructCanaryCorruption();

    testStructHashCorruption();
#endif // STRUCT_PROTECT

#endif // DEBUG

#ifndef DEBUG
    printf("MEOW:)\n");
#endif // DEBUG

    return 0;
}


