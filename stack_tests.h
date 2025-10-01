#ifndef _TESTS_H_
#define _TESTS_H_


void testNormal();


#ifdef CANARY
void testCanaryCorruption();
#endif // CANARY


#ifdef POISON
void testPoisonCorruption();
#endif // POISON


#ifdef HASH
void testHashCorruption();
#endif // HASH


void testUnderflow();


#endif // _TESTS_H_
