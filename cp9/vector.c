#include "vector.h"

// Инициализация вектора заданного размера
void create(vector* v, size_t size) {
    v->size = size;                                 // Устанавливаем размер вектора
    v->data = (value*)malloc(size * sizeof(value)); // Выделяем память под массив данных

    // Инициализируем каждый элемент вектора
    for (int i = 0; i < size; i++) {
        v->data[i].key = 0.0;         // Устанавливаем ключ элемента в 0.0 (тип double)
        strcpy(v->data[i].string, ""); // Устанавливаем строковое значение элемента как пустую строку
    }
}

// Проверка на пустоту вектора
bool empty(vector* v) {
    return v->size == 0;
}

// Получение размера вектора
int sizeV(vector* v) {
    return v->size;
}

// Загрузка значения по индексу вектора
value load(vector* v, int i) {
    value emptyValue;
    emptyValue.key = 0.0;
    strcpy(emptyValue.string, "");

    // Проверка на допустимый диапазон индекса
    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return emptyValue; // Возвращаем пустое значение, если индекс недопустим
    }
}

// Запись значения по индексу вектора
void write(vector* v, int i, value val) {
    // Проверка на допустимый диапазон индекса
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

// Изменение размера вектора
void resize(vector* v, size_t size) {
    value* new_values = (value*)realloc(v->data, size * sizeof(value)); // Перевыделяем память под массив данных
    v->data = new_values;
    v->size = size;

    // Если новый размер меньше предыдущего, инициализируем дополнительные элементы
    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            v->data[i].key = 0.0;
            strcpy(v->data[i].string, "");
        }
    }
}

// Освобождение памяти, занимаемой вектором
void destroy(vector* v) {
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

// Вывод содержимого вектора в консоль
void printT(vector* v) {
    int size_of_Vector = sizeV(v);
    printf("._______________________________________________________.\n");
    printf("|     Key      |                Meaning                 |\n");
    printf("|______________|________________________________________|\n");
    for (int i = 0; i < size_of_Vector; i++) {
        value tmp = load(v, i);
        printf("| %12lf | %-39s|\n", tmp.key, tmp.string);
    }
    printf("|______________|________________________________________|\n");
}

// Обмен значениями между двумя элементами
void swap(value* x, value* y) {
    value temp = *x;
    *x = *y;
    *y = temp;
}
