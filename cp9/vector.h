#ifndef SORT
#define SORT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define maxn 1000
#define INF 1000000000
#define STRSIZE 100

// Структура, представляющая элемент данных вектора
typedef struct value {
    double key;          // Ключ элемента (тип double)
    char string[STRSIZE]; // Строковое значение элемента
} value;

// Структура, представляющая вектор
typedef struct {
    value* data; // Указатель на массив данных
    int size;    // Размер вектора
} vector;

// Перечисление, представляющее тип сортировки вектора
typedef enum {
    unsorted,  // Несортированный
    ascending, // Сортировка по возрастанию
    descending // Сортировка по убыванию
} sortType;

// Инициализация вектора заданного размера
void create(vector* v, size_t size);

// Проверка на пустоту вектора
bool empty(vector* v);

// Получение размера вектора
int sizeV(vector* v);

// Загрузка значения по индексу вектора
value load(vector* v, int i);

// Запись значения по индексу вектора
void write(vector* v, int i, value val);

// Изменение размера вектора
void resize(vector* v, size_t size);

// Освобождение памяти, занимаемой вектором
void destroy(vector* v);

// Вывод содержимого вектора в консоль
void printT(vector* v);

// Обмен значениями между двумя элементами
void swap(value* x, value* y);

// Бинарный поиск в векторе по ключу
value binarySearch(vector* table, double key);

// Обратный бинарный поиск в векторе по ключу
value reverseBinarySearch(vector* table, double key);

// Получение типа сортировки вектора
sortType getSortTable(vector* table);

// Турнирная сортировка вектора
void tournamentSort(vector* v);

#endif // SORT
