#ifndef _TESTS_H_
#define _TESTS_H_


/// Тестирование стандартной работы стека
void testNormal();


/// Тестирование ошибки пустого стека
void testUnderflow();


#ifdef CANARY
/// Тестирование канареек стека в режиме CANARY
void testStackCanaryCorruption();
#endif // CANARY


#ifdef POISON
/// Тестирование яда в режиме POISON
void testPoisonCorruption();
#endif // POISON


#ifdef HASH
/// Тестирование хеша стека в режиме HASH
void testStackHashCorruption();
#endif // HASH


#ifdef STRUCT_PROTECT
/// Тестирование хеша структуры стека в режиме STRUCT_PROTECT
void testStructCanaryCorruption();


/// Тестирование канареек структуры стека в режиме STRUCT_PROTECT
void testStructHashCorruption();
#endif // STRUCT_PROTECT


#endif // _TESTS_H_
