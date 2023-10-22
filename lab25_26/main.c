#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

//D5 - слияние двух деков с сохранением порядка, сортировка слиянием

void print_menu() {
    printf("\nВыберите действие\n");
    printf("0)Выход\n");
    printf("1)Вывести содержимое дека\n");
    printf("2)Узнать размер дека\n");
    printf("3)Добавить элемент спереди\n");
    printf("4)Добавить элемент сзади\n");
    printf("5)Удалить элемент спереди\n");
    printf("6)Удалить элемент сзади\n");
    printf("7)Сортировка слияением\n");
    printf("8)Опустошить дек\n");
    printf("\n");
}


int main() {
    deque* s1 = (deque*)malloc(sizeof(deque));
    deque* s2 = (deque*)malloc(sizeof(deque));
    initdeque(s1);
    initdeque(s2);
    int choose = 1;
    int value;
    int size;
    while(choose) {
        print_menu();
        scanf("%d", &choose);
        switch(choose) {
        case 0:
            deletedeque(s1);
            deletedeque(s2);
            free(s1);
            free(s2);
            return 0;
        case 1:
            printdeque(s1);
            break;
        case 2:
            size = size_deque(s1);
            printf("Размер дека: %d\n", size);
            break;
        case 3:
            printf("Введите значение элемента: ");
            scanf("%d", &value);
            push_front(s1, value);
            break;
        case 4:
            printf("Введите значение элемента: ");
            scanf("%d", &value);
            push_back(s1, value);
            break;
        case 5:
            pop_front(s1);
            size = size_deque(s1);
            if (size > 0) {
                printf("Элемент удалён\n");
            } else {
                printf("Дек пуст\n");
            }
            break;
        case 6:
            pop_back(s1);
            size = size_deque(s1);
            if (size > 0) {
                printf("Элемент удалён\n");
            } else {
                printf("Дек пуст\n");
            }
            break;
        case 7:
            merge_sort(s1);
            printdeque(s1);
            break;
        case 8:
            deletedeque(s1);
            printf("Дек пуст\n");
            break;
        default:
            printf("Указанного действия не существует");
            break;
        }
    }
    return 0;
}
