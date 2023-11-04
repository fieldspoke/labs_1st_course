#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void listInit(List* list) {
    list->front = malloc(sizeof(List_node)); // Создаем барьерный элемент
    list->front->next = NULL;
    list->size = 0;
}

int listIsEmpty(List* list) {
    return list->size == 0;
}

color convertColor(char* str) {
    if ((!strcmp(str, "Red")) || (!strcmp(str, "red"))) {
        return Red;
    } else if ((!strcmp(str, "Green")) || (!strcmp(str, "green"))) {
        return Green;
    } else if ((!strcmp(str, "Blue")) || (!strcmp(str, "blue"))) {
        return Blue;
    } else if ((!strcmp(str, "Yellow")) || (!strcmp(str, "yellow"))) {
        return Yellow;
    } else if ((!strcmp(str, "Black")) || (!strcmp(str, "black"))) {
        return Black;
    } else {
        printf("This color is not in the enum list. Please enter a valid color.\n");
        return -1;  // Возвращаем недопустимое значение, чтобы обозначить ошибку
    }
}

char* convertEnum(color clr) {
    switch (clr)
    {
    case 0:
        return "Red";
        break;
    case 1:
        return "Green";
        break;
    case 2:
        return "Blue";
        break;
    case 3:
        return "Yellow";
        break;
    case 4:
        return "Black";
    }
}

void listPushFront(List* list, color clr) {
    List_node* listNode = malloc(sizeof(List_node));
    listNode->value = clr;

    listNode->next = list->front->next;
    list->front->next = listNode; // Вставляем новый элемент после барьерного элемента

    list->size++;
}

void listInsertIndex(List* list, color clr, int index) {
    if (index > list->size || index < 0) {
        printf("\tOut of bounds list\n");
        return;
    }

    List_node* listNode = malloc(sizeof(List_node));
    listNode->value = clr;

    List_node* tmp = list->front; // Начинаем с барьерного элемента

    for (int i = 0; i < index; i++) {
        tmp = tmp->next;
    }

    listNode->next = tmp->next;
    tmp->next = listNode;

    list->size++;
}

void listPopIndex(List* list, int index) {
    if (index >= list->size || index < 0) {
        printf("\tOut of bounds list\n");
        return;
    }

    List_node* tmp = list->front;

    for (int i = 0; i < index; i++) {
        tmp = tmp->next;
    }

    List_node* toRemove = tmp->next;
    tmp->next = toRemove->next;

    char* res = convertEnum(toRemove->value);
    printf("\tRemoved element: %s\n", res);
    free(toRemove);

    list->size--;
}

void listPrintout(List* list) {
    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        return;
    }

    List_node* tmp = list->front->next; // Начинаем с элемента после барьерного элемента

    printf("\tList:\n");
    for (int i = 0; i < list->size; i++) {
        char* res = convertEnum(tmp->value);
        printf("%s\t", res);
        tmp = tmp->next;
    }

    printf("\n");
}

void listRemove(List* list, bool is_exit) {
    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        if(is_exit){
            free(list->front); //если список пуск и мы выходим из программы, то удаляем барьерный элемент
        }
        return;
    }

    List_node* tmp = list->front->next;

    while (tmp != NULL) {
        List_node* next = tmp->next;
        free(tmp);
        tmp = next;
    }

    // Удаляем барьерный элемент
    free(list->front);
    
    // Переинициализируем список в случае, когда мы не выходим из программы и список ещё будет использоваться
    if(!is_exit){
        listInit(list);
    }
}


int isListOrdered(List* list) {
    if (listIsEmpty(list)) {
        // Пустой список считается упорядоченным
        return 1;
    }

    List_node* current = list->front->next; // Начинаем с элемента после барьерного элемента
    while (current->next != NULL) {
        if (current->value > current->next->value) {
            // Если текущий элемент больше следующего, список не упорядочен
            return 0;
        }
        current = current->next;
    }

    // Если прошли по всем элементам и не нашли нарушений, то список упорядочен
    return 1;
}
