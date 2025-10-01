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

#ifdef CANARY
    testCanaryCorruption();
#endif // CANARY IN DEBUG

#ifdef POISON
    testPoisonCorruption();
#endif // POISON IN DEBUG

#ifdef HASH
    testHashCorruption();
#endif // HASH IN DEBUG

    testUnderflow();
#endif // DEBUG

    return 0;
}


