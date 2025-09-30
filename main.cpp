#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_tests.h"


int main()
{
#ifdef DEBUG
    testNormal();

    testCanaryCorruption();

    testPoisonCorruption();

    testHashCorruption();

    testUnderflow();
#endif

    return 0;
}


