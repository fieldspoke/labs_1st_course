#ifndef deque_h
#define deque_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct element {
    int value; //значение
    struct element *next; //указ на след элемент
    struct element *prev; //указ на пред элемент
} element;

typedef struct deque {
    element *first; //первый элемент
    element *last; //последний элемент
    int size; //рамзер
} deque;

void initdeque(deque *D);
int size_deque(deque *D);
bool empty_deque(deque *D);
void push_front(deque *D, int value);
void push_back(deque *D, int value);
int value_front(deque *D);
int value_back(deque *D);
void pop_front(deque *D);
void pop_back(deque *D);
void deletedeque(deque *D);
void printdeque(deque *D);

void merge_sort(deque *s);
void merge(deque *res, deque *s1, deque *s2);

#endif