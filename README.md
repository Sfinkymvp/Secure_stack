# Secure stack

---

Безопасная реализация стека

## Зависимости

- `g++` Компилятор C++
- `make` Утилита для автоматизации сборки

## Флаги компиляции

- `-DDEBUG`           Режим отладки 
- `-DCANARY`          Стековые канарейки 
- `-DPOISON`          POISON значения 
- `-DHASH`            Хеш стека 
- `-DSTRUCT_PROTECT` Защита структуры стека (hash + canary) 
- `-DHARD`            Остановка программы при ошибке 

## Сборка

```bash
git clone https://github.com/Sfinkymvp/Secure_stack
cd Secure_stack
```

Запуск программы в debug режиме:
```bash
make debug
./stack
```

Запуск программы в обычном режиме:
```bash
make release
./stack
```

--- 
