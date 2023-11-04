#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"


//Вариант [3,3,12] - перечислимый тип, односвязный с барьерным эл-ом, проверить на упорядочивание (я сделал по возрастанию)


void helpBoard() {
    printf("\tHELP BOARD\n\n");
    printf("\tCommand programms:\n");
    printf("exit \tExit to program\n");
    printf("help \tCall help board\n");
    printf("pushf \tPush front element\n");
    printf("insind \tInsert element by index\n");
    printf("popind \tPop element by index\n");
    printf("print \tPrint all elements in list\n");
    printf("dellist\tDelete all elements in list\n");
    printf("vartask\tProve that list is ordered\n");
    printf("\n\t ENUM COLORS:\n");
    printf("Red\nGreen\nBlue\nYellow\nBlack\n\n");
}

int main() {
    List list;
    listInit(&list);
    bool is_exit = false;
    char str[9];
    helpBoard();
    
    while (1) {
        printf("\n");
        printf("Enter command: ");
        scanf("%8s", str);  
        
        if (!strcmp(str, "exit")) {
            is_exit = true;
            listRemove(&list, is_exit);
            exit(1);
        } else if (!strcmp(str, "help")) {
            helpBoard();
        } else if (!strcmp(str, "pushf")) {
            printf("Enter a color to push front: ");
            char stringColor[10];
            scanf("%s", stringColor);
            color clr = convertColor(stringColor);
            if (clr != -1) {
                listPushFront(&list, clr);
            }
        } else if (!strcmp(str, "insind")) {
            printf("Enter the index of the element to be added: ");
            int index;
            scanf("%d", &index);
            printf("Enter a color to add to the list: ");
            char stringColor[10];
            scanf("%s", stringColor);
            color clr = convertColor(stringColor);
            if (clr != -1) {
                listInsertIndex(&list, clr, index);
            }
        } else if (!strcmp(str, "popind")) {
            printf("Enter the index of the element to delete: ");
            int index;
            scanf("%d", &index);
            listPopIndex(&list, index);
        } else if (!strcmp(str, "print")) {
            listPrintout(&list);
        } else if (!strcmp(str, "dellist")) {
            listRemove(&list, is_exit);
        } else if (!strcmp(str, "vartask")) {
            if (isListOrdered(&list)) {
                printf("The list is ordered.\n");
            } else {
                printf("The list is not ordered.\n");
            }
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}
