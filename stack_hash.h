#ifndef _STACK_HASH_H_
#define _STACK_HASH_H_


#include <stdio.h>

#include "stack_data.h"


/// Вычисляет хеш для переданного участка памяти
/// @param data Указатель на участок памяти
/// @param size Размер участка памяти в байтах
/// @return Хеш
size_t djb2(const unsigned char* data, size_t size);


/// Проверяет совпадение значений хеша в стеке
/// @param stack Указатель на структуру стека
/// @return true - хеш совпадает, иначе false
bool checkStackHash(const Stack_t* stack);


/// Вычисляет хеш для стека
/// @param stack Указатель на структуру стека
void calculateStackHash(Stack_t* stack);


#ifdef STRUCT_PROTECT
/// Проверяет совпадение значений хеша в структуре стека \n
/// Определена в режиме STRUCT_PROTECT 
/// @param stack Указатель на структуру стека
/// @return true - хеш совпадает, иначе false
bool checkStructHash(const Stack_t* stack);


/// Вычисляет хеш для структуры стека \n
/// Определена в режиме STRUCT_PROTECT
/// @param stack Указатель на структуру стека
void calculateStructHash(Stack_t* stack);
#endif // STRUCT_PROTECT


#endif // _STACK_HASH_H_
