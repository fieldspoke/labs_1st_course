//Полятыкин Н. М8О-104Б-22 Лаб.23 Вар.21

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum {
    EXIT,
    ADD,
    PRINT,
    FUNCTION

} Operations;

typedef struct binaryTree_s { //ввдем структуру дерева
    int data; //данные узла
    int deep; //глубина узла
    struct binaryTree_s *left; //указатель на левое поддерево
    struct binaryTree_s *right; //указатель на правое поддерево
} binaryTree;

binaryTree *createNode(int data) { //создать новый узел
    binaryTree *newNode = (binaryTree *)malloc(sizeof(binaryTree)); //выделение памяти под новый узел

    if (newNode == NULL) { 
        printf("Malloc returned NULL\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int comparison_min_depth(int deep, int depth){ //сравнение глубины данного терминального узла с наименьшей глубиной среди предыдущих листов
    if (depth < 0){
        return deep;
    }

    else if (depth > 0 && depth < deep){ //сраниваются значения минимальной глубины среди ранее рассмотренных листов дерева и глубины текущего листа, возвращается минимальное из двух чисел
            return depth;
    }

    else {
        return deep;
    }
}


void push_new_elem(binaryTree **tree, int data) { //добавление нового элемента в дерево

    binaryTree *tmp = *tree;

    if (tmp == NULL) {
        binaryTree *newNode = createNode(data);
        *tree = newNode;
        newNode->deep = 1;
    }

    else if (data < tmp->data) { //если значение нового узла меньше значения узла дерева, то идём влево
 
        if (tmp->left == NULL) { //если у узла отсуствует левый потомок, то он создаётся
            binaryTree *newNode = createNode(data);
            tmp->left = newNode;          
            newNode->deep = tmp->deep + 1; //у нового узла глубина становится на один уровень ниже родительского узла
        }

        else {
            push_new_elem(&(tmp->left), data); //если левый потомок есть, то идём в него
        }
    }

    else if (data > tmp->data) {//если значение нового узла больше значения узла дерева, то идём вправо

        if (tmp->right == NULL) {//если у узла отсуствует правый потомок, то он создаётся
            binaryTree *newNode = createNode(data);
            tmp->right = newNode;
            newNode->deep = tmp->deep + 1;
        }

        else {
            push_new_elem(&(tmp->right), data); //если правый потомок есть, то идём в него
        }
    }
}


int find_leaf_min_depth(binaryTree *tree, int min_depth) { //функция нахождения минимальной глубины листа дерева

    if (tree == NULL) {
        return 0;
    }

    else {

        if (tree->left != NULL) { //если левый потомок есть, идём в него
            min_depth = find_leaf_min_depth(tree->left, min_depth);
        }

        if (tree->right != NULL) { //если правый потомок есть, идём в него
            min_depth = find_leaf_min_depth(tree->right, min_depth);
        }

        if (tree->left == NULL && tree->right == NULL){ //если данный узел не имеет потомков, т.е. является терминальным (листом), то будем сравнивать глубину данного листа с минимальной глубиной среди ранее рассмотренных листов
            min_depth = comparison_min_depth(tree->deep, min_depth);   
       }

       return min_depth;

    }
}


void clear_all_tree(binaryTree *tree) { //рекурсивное удаление дерева и освобождение памяти после окончания работы с ним

    if (tree == NULL) {

        return;
    }
    else {

        if (tree->left != NULL) {
            clear_all_tree(tree->left);
            tree->left = NULL;

        }
        if (tree->right != NULL) {
            clear_all_tree(tree->right);
            tree->right = NULL;
        }

        free(tree);

    }
}


void tree_print(binaryTree *tree, int n) { //функция вывода дерева
    if (tree != NULL) {
        tree_print(tree->right, n + 1);
        for (int i = 0; i < n; i++) {
            printf("\t");
        }
            printf("%d\n", tree->data);
            tree_print(tree->left, n + 1);
        
    }
}

void print_menu() { //функция объявления меню
    printf("\nВыберите дейcтвие и введите его номер:\n0) Выход\n");
    printf("1) Ввести в дерево элемент.\n");
    printf("2) Распечатать дерево.\n");
    printf("3) Определить глубину минимального элемента.\n");
}


int main() {

    binaryTree *tree = NULL;
    int min_depth_leaf = 1;
    int node_data = 0;
    Operations op = ADD;

    while (op){    
        print_menu();
        printf("\nВведите номер действия: ");

        if(scanf("%d", &op) <= 0){
            printf("\nТакого действия нет. \n");
            clear_all_tree(tree);
            break;
        }

        switch (op) {
            case ADD:
                printf("\nВведите значение нового узла: ");
                scanf("%d", &node_data);
                push_new_elem(&tree, node_data);
                break;
            case PRINT:
                printf("\n_________________\n");
                tree_print(tree, 1);
                printf("\n_________________\n");
                break;
            case FUNCTION:
                printf("\n");
                int min_depth_leaf = find_leaf_min_depth(tree, 0);
                printf("\nМининмальная глубина листа двоичного дерева: %d \n", min_depth_leaf);
                break;
            case EXIT:
                clear_all_tree(tree);
                printf("\nДерево удалено, выделенная память освобождена.\n");
                op = 0;
                break;
            default:
                printf("\nТакого действия нет. \n");
                break;
        }
    }
    return 0;

}