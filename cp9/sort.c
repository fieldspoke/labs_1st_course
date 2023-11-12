#include "vector.h"

// Поиск элемента в отсортированном векторе по ключу (бинарный поиск)
value binarySearch(vector* table, double key) {
    long left = 0;
    long right = sizeV(table) - 1;
    long middle;
    value def = {0.0, ""}; // Значение по умолчанию, если ключ не найден

    while (left <= right) {
        middle = (left + right) / 2;

        if (key < table->data[middle].key) {
            right = middle - 1;
        } else if (key > table->data[middle].key) {
            left = middle + 1;
        } else {
            return table->data[middle]; // Возвращаем элемент с найденным ключом
        }
    }

    return def; // Возвращаем значение по умолчанию, если ключ не найден
}

// Обратный бинарный поиск в отсортированном векторе по ключу
value reverseBinarySearch(vector* table, double key) {
    long left = sizeV(table) - 1;
    long right = 0;
    value def = {0.0, ""}; // Значение по умолчанию, если ключ не найден

    while (left >= right) {
        long middle = (left + right) / 2;

        if (key < table->data[middle].key) {
            right = middle + 1;
        } else if (key > table->data[middle].key) {
            left = middle - 1;
        } else {
            return table->data[middle]; // Возвращаем элемент с найденным ключом
        }
    }

    return def; // Возвращаем значение по умолчанию, если ключ не найден
}

// Определение типа сортировки вектора (по возрастанию, убыванию, несортированный)
sortType getSortTable(vector* table) {
    int Asc = 1;
    int Des = 1;
    int size = sizeV(table);

    // Проверка порядка сортировки элементов
    for (int i = 0; i < size - 1; i++) {
        value a = load(table, i);
        value b = load(table, i + 1);

        if (a.key > b.key) {
            Asc = 0; // Если есть хотя бы одно нарушение порядка возрастания, Asc устанавливаем в 0
        } else if (a.key < b.key) {
            Des = 0; // Если есть хотя бы одно нарушение порядка убывания, Des устанавливаем в 0
        }
    }
    
    // Возвращаем тип сортировки
    if (Des) {
        return descending; // Если все элементы упорядочены по убыванию
    } else if (Asc) {
        return ascending; // Если все элементы упорядочены по возрастанию
    } else {
        return unsorted; // Если порядок не определен (вектор несортированный)
    }
}

// Сортировка вектора методом турнирной сортировки
void tournamentSort(vector* v) {
    int n = v->size;
    value* a = v->data;

    // Проходим по элементам массива, формируя бинарное дерево турнира
    for (int i = n - 1; i > 0; i--) {
        for (int j = (i - 1) / 2; j >= 0; j--) {
            int l = 2 * j + 1;
            if (l < i && a[l].key < a[l + 1].key) {
                l++;
            }
            if (a[j].key < a[l].key) {
                swap(&a[j], &a[l]); // Обмениваем значения, чтобы сохранить порядок турнира
            }
        }
        swap(&a[0], &a[i]); // Перемещаем максимальный элемент в конец массива
    }
}
