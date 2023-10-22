#include "deque.h"

void initdeque(deque *D) {
    D->size = 0;
    D->first = NULL;
    D->last = NULL;
}

int size_deque(deque *D) { //функция, вычисляющая значение дека
    return D->size;
}


bool empty_deque(deque *D) {
    if (D->size == 0) {
        return true;
    }
    return false;
}

void push_front(deque *D, int value) {
    element *tmp = (element *) malloc(sizeof(element)); //выделяем память на элемент
    tmp->value = value;//передаем ему значение из аргумента функции
    tmp->prev = NULL; //так как добавили спереди, то перед ним пусто
    tmp->next = D->first; // следующий для нашего элемента это бывший первый
    if (D->first) {
        D->first->prev = tmp; //теперь предыдущий для бывшего первого - новый
    }
    D->first = tmp; //теперь первый элемент в деке - новый элемент
    if (!D->last) { //если дек пуст
        D->last = tmp;
    }
    D->size++; //увеличиваем размер дека
}

void push_back(deque *D, int value) { //добавление в конец
    element *tmp = (element *) malloc(sizeof(element)); //выделяем память
    tmp->value = value; //передаем значение
    tmp->next = NULL; //очевидно что след элемент - пустой
    tmp->prev = D->last; //указатель на предыдущий - последний элемент дека
    if (D->last) { //если есть последний
        D->last->next = tmp;
    }
    D->last = tmp; //последний - новый
    if (!D->first) { //если дек пуст
        D->first = tmp;
    }
    D->size++; //увеличиваем размер дека
}



void pop_front(deque *D) {//взятие спереди
    element *tmp = D->first;
    D->first = tmp->next;
    if (D->size == 1) D->last = NULL;
    free(tmp);
    tmp = NULL;
    D->size--; //уменьшаем размер
}


void pop_back(deque *D) { //взятие с конца
    element *tmp = D->last;
    D->last = tmp->prev;
    if (D->size == 1) D->first = NULL;
    free(tmp);
    tmp = NULL;
    D->size--; //уменьшаем размер

}

int value_front(deque *D) {
    if (empty_deque(D)) {
        printf("Дек пуст!\n");
        return 1;
    }
    return D->first->value;
}

int value_back(deque *D) {
    if (empty_deque(D)) {
        printf("Дек пуст!\n");
        return 1;
    }
    return D->last->value;
}


void deletedeque(deque *D) {
    int i = 0;
    element *tmp = D->first;
    for (i = size_deque(D); i > 0; i--) {
        element *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(D);
}



void printdeque(deque *D) { //вывод дека
    if (empty_deque(D)) { //если пустой
        printf("\n Дек пустой! \n");
    } else {
        printf("\n ( "); //скобка для вида
        element *tmp = D->first; //объявляем элемент, который будем выводить
        while (tmp) { //пока элемент существует в деке
            printf("%d ", tmp->value); //вывод
            tmp = tmp->next; //сдвигаем на следующий
        }
        printf(")\n"); //закрываем скобку
    }
}


void merge(deque *res, deque *s1, deque *s2) {
    deque s3;
    initdeque(&s3);

    while (!empty_deque(s1) && !empty_deque(s2)) {
        if (value_back(s1) > value_back(s2)) {
            push_back(&s3, value_back(s1));
            pop_back(s1);
        } else {
            push_back(&s3, value_back(s2));
            pop_back(s2);
        }
    }
    while (!empty_deque(s1)) {
        push_back(&s3, value_back(s1));
        pop_back(s1);
    }
    while (!empty_deque(s2)) {
        push_back(&s3, value_back(s2));
        pop_back(s2);
    }

    while (!empty_deque(&s3)) {
        push_back(res, value_back(&s3));
        pop_back(&s3);
    }
}

// Сортировка слиянием
void merge_sort(deque *s) {
    if (s->size > 1) {
        deque s2, s3;
        initdeque(&s2);
        initdeque(&s3);
        while (!empty_deque(s)) {
            if (size_deque(s) % 2 == 0) {
                push_front(&s2, value_front(s));
                pop_front(s);
            } else {
                push_front(&s3, value_front(s));
                pop_front(s);
            }
        }
        merge_sort(&s2);
        merge_sort(&s3);
        merge(s, &s2, &s3);
    }
}