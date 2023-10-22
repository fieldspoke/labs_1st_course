#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define MAX_EXPRESSION_LENGTH 100

void next_symbol(Symbol* symbol, char input[]) {
    static int index = 0;
    char c = input[index];
    static SymbolType prev = symb_NONE;
    if (c == '\0') {  // проверяем на конец строки
        symbol->type = symb_NONE;
        prev = symb_NONE;
        return;
    }

    if (isdigit(c)) {
        symbol->type = symb_NUMBER;
        symbol->data.number = c - '0';
        index++;  // двигаемся дальше по строке

        // Считываем все цифры числа
        while (isdigit(input[index])) {
            symbol->data.number = symbol->data.number * 10 + (input[index] - '0');
            index++;
        }
    } else if (isOperator(c)) {
        symbol->type = symb_OP;
        symbol->data.op = c;
        index++;  // двигаемся дальше по строке
    } else if (isalpha(c)) {
        symbol->type = symb_VAR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == '(') {
        symbol->type = symb_LEFT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == ')') {
        symbol->type = symb_RIGHT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == '-') {
        symbol->type = symb_OP;
        if (prev == symb_OP || prev == symb_NONE) {
            symbol->data.op = OP_UNARY_MINUS;
        } else {
            symbol->data.op = OP_MINUS;
        }
        index++;  // двигаемся дальше по строке
    } else {
        symbol->type = symb_NONE;
        index++;  // двигаемся дальше по строке
    }
    prev = symbol->type;
}

void infixToPostfix(char exp[], node** expression) {
    stack* s = malloc(sizeof(stack));
    initStack(s);

    Symbol t;
    next_symbol(&t, exp);

    while (t.type != symb_NONE) {
        switch (t.type) {
            case symb_NONE:
                fprintf(stderr, "Ошибка! символ %c не распознан\n", t.data.c);
                return;

            case symb_OP:
                for (;;) {
                    if (stackEmpty(s))
                        break;

                    Symbol top = stackTopSymbol(s);

                    if (top.type != symb_OP)
                        break;

                    if ((op_assoc(t.data.op) == ASSOC_LEFT && getPriority(t.data.op) <= getPriority(top.data.op)) ||
                        (op_assoc(t.data.op) == ASSOC_RIGHT && getPriority(t.data.op) < getPriority(top.data.op))) {
                        pushBack(expression, top);
                        stackPopSymbol(s);
                    } else {
                        break;
                    }
                }
                stackPushSymbol(s, t);
                break;

            case symb_NUMBER:
            case symb_VAR:
                pushBack(expression, t);
                break;

            case symb_LEFT_BR:
                stackPushSymbol(s, t);
                break;

            case symb_RIGHT_BR:
                while (!stackEmpty(s) && stackTopSymbol(s).type != symb_LEFT_BR) {
                    pushBack(expression, stackPopSymbol(s));
                }

                if (stackEmpty(s)) {
                    fprintf(stderr, "Ошибка: пропущена скобка\n");
                    return;
                }

                stackPopSymbol(s);
                break;
        }

        next_symbol(&t, exp);
    }

    while (!stackEmpty(s)) {
        if (stackTopSymbol(s).type == symb_LEFT_BR) {
            fprintf(stderr, "Ошибка: пропущена скобка\n");
            return;
        }

        pushBack(expression, stackPopSymbol(s));
    }

    stackDestroy(s);
}

Tree* postfixToTree(node* postfix) {
    stack* s = malloc(sizeof(stack));
    initStack(s);
    for(node* current = postfix; current != NULL; current = current->next) {
        Symbol c = current->data;
        if (c.type != symb_OP) {
            Tree* tmp = createTree(c);
            stackPushTree(s, tmp);
        } else if (c.type == symb_OP) {
            Tree* right = stackPopTree(s);
            Tree* left = stackPopTree(s);
            Tree* op = createTree(c);
            op->left = left;
            op->left->parent = op;
            op->right = right;
            op->right->parent = op;
            stackPushTree(s, op);
        }
    }
    Tree* res = stackPopTree(s);
    res->parent = NULL;
    stackDestroy(s);
    return res;
}

bool is_in_denominator(Tree* node){
    
    if(node->parent->value.data.op == OP_DIVIDE && node->parent->right == node){
        return true;
    }
    else{
        return false;
    }
}

bool is_division_symb_func(Tree* node){


    if(node->value.type == symb_OP && node->value.data.op == OP_DIVIDE){
        return true;
    }
    else{
        return false;
    }

}

bool have_same_divider(float a, float b){

    int i;

    int x = (int)a;
    int y = (int)b;

    for (i = 2; i <= x; i++){
        if (x%i == 0 && y%i == 0){
            return true;
        }
    }
    return false;

}

float find_NOD_func(float a, float b){
    int max;
    int min;

    if (a >= b){
        max = (int)a;
        min = (int)b;

    }
    else{
        max = (int)b;
        min = (int)a;
    }
    int i;
    for (i = max; i >= 2; i--){
        if ((int)a%i == 0 && (int)b%i == 0){
            return (float)i;
        }
    }
    return (float)min;
}

void clear_leaf(Tree* node){

    if (node->parent->parent == NULL){
        node->parent->right = NULL;
        free(node);
    }

    else{
        if(node->parent->left == node){
            node->parent->parent->left = node->parent->right;
            node->parent->right->parent = node->parent->parent;
            node->parent->left = NULL;
            free(node->parent);
            free(node);
        }
        else{
            node->parent->parent->left = node->parent->left;
            node->parent->left->parent = node->parent->parent;    
            node->parent->right = NULL;
            free(node->parent);
            free(node);
        }
    }
}


bool is_above_div_symb(Tree* node){

    if(node->parent->value.type == symb_OP && node->parent->value.data.op == OP_DIVIDE && node->parent->left == node){
        return true;
    }
    else{
        return false;
    }
}

bool cond_for_division(bool is_divider, bool is_division_symb, float number, Tree* original, Tree* tmp){//проверка на условие деления


    if ((is_divider == true && is_division_symb == false) || (is_divider == false && is_division_symb == true)){
        bool have_division = have_same_divider(original->value.data.number, tmp->value.data.number);
        if(have_division == true){
            float NOD = find_NOD_func(original->value.data.number, tmp->value.data.number);

            if ((original->value.data.number)/NOD == 1 && (tmp->value.data.number)/NOD == 1){
                if (is_above_div_symb(original)){
                    original->value.data.number = 1;
                }
                else{
                    clear_leaf(original);
                }
                if (is_above_div_symb(tmp)){
                    tmp->value.data.number = 1;
                }
                else{
                    clear_leaf(tmp);
                }
            }
            else if ((original->value.data.number)/NOD == 1){
                if (is_above_div_symb(original)){
                    original->value.data.number = 1;
                }
                else{
                    clear_leaf(original);
                }
                tmp->value.data.number = (tmp->value.data.number)/NOD;
            }
            else if ((tmp->value.data.number)/NOD == 1){
                if (is_above_div_symb(tmp)){
                    tmp->value.data.number = 1;
                }
                else{
                    clear_leaf(tmp);
                }
                original->value.data.number = (original->value.data.number)/NOD;
            }
            else{
                original->value.data.number = (original->value.data.number)/NOD;
                tmp->value.data.number = (tmp->value.data.number)/NOD;
            }//перебираются все случаи, когда возможно сокрщение
            return true;//в случае преобразования дерева(сокрщения) возращается значение trues
        }
    }
    return false;
}

bool cond_for_division_var(bool is_divider, bool is_division_symb, Tree* original, Tree* tmp){


    if ((is_divider == true && is_division_symb == false) || (is_divider == false && is_division_symb == true)){
        if(original->value.data.c == tmp->value.data.c){

            if (is_above_div_symb(original) == true && is_above_div_symb(tmp) == false){
                original->value.type = symb_NUMBER;
                original->value.data.number = 1;
                clear_leaf(tmp);
            }
            else if (is_above_div_symb(tmp) == true && is_above_div_symb(original) == true){
                tmp->value.type = symb_NUMBER;
                tmp->value.data.number = 1;
                clear_leaf(original);
            }
            else if (is_above_div_symb(tmp) == false && is_above_div_symb(original) == false){
                clear_leaf(original);
                clear_leaf(tmp);
            }
            return true;
        }
    }
    return false;
}

bool find_divider_in_tree(Tree* node, float number){//поиск делителей в дереве


    bool is_divider = is_in_denominator(node);
    bool is_division_symb = is_division_symb_func(node);
    bool tree_is_changed = false;


    Tree* original = node;//два указателя: один сохраняет переданный в функцию лист, второй - пробегается по дереву
    Tree* tmp = node;

    if (tmp->parent->right == tmp){
        tmp = tmp->parent;
    }

    while (tmp->parent != NULL){

        if (tmp->parent == NULL){
        }  

        tmp = tmp->parent;

        is_division_symb = is_division_symb_func(tmp);

        if (tmp->right == NULL){
        }

        if (tmp->right != NULL){
            if (tmp->right->value.type == symb_NUMBER){// если есть правый потомок и это число, проверяется условие на возможность деления
                tree_is_changed = cond_for_division(is_divider, is_division_symb, number, original, tmp->right);
                if(tree_is_changed){
                    return tree_is_changed;
                }
            }
        }

    }
    return false;
}

bool find_divider_in_tree_var(Tree* node, char var){//поиск делителей в дереве

    bool is_divider = is_in_denominator(node); 
    bool is_division_symb = is_division_symb_func(node);
    bool tree_is_changed = false;

    Tree* original = node;//два указателя: один сохраняет переданный в функцию лист, второй - пробегается по дереву
    Tree* tmp = node;

    if (tmp->parent->right == tmp){
        tmp = tmp->parent;
    }

    while (tmp->parent != NULL){

        if (tmp->parent == NULL){
        }  

        tmp = tmp->parent;

        is_division_symb = is_division_symb_func(tmp);

        if (tmp->right == NULL){
        }

        if (tmp->right != NULL){
            if (tmp->right->value.type == symb_VAR){// если есть правый потомок и это буква, проверяется условие на возможность деления
                tree_is_changed = cond_for_division_var(is_divider, is_division_symb, original, tmp->right);
                if(tree_is_changed){
                    return tree_is_changed;
                }
            }
        }
    }
    return false;
}


void simplify_tree(Tree* node, Tree* node_tree){

    if (node == NULL){
        return;
    }


    if (node -> left != NULL){//если есть левый потомок - идём в него
        simplify_tree(node -> left, node_tree);
    }

    if (node -> right != NULL){//если есть правый потомок - идём в него
        simplify_tree(node -> right, node_tree);
    }

    if (node -> left == NULL && node -> right == NULL){//если нашли лист - запускаем функцию поиска возможного делителя в дереве
        if (node -> value.type == symb_NUMBER){
            if(find_divider_in_tree(node, node -> value.data.number)){//если дерево было изменено - начинаем
                simplify_tree(node_tree, node_tree);
            }
        }
        else{//аналогично с переменными
            if(find_divider_in_tree_var(node, node->value.data.c)){
                simplify_tree(node_tree, node_tree);
            }
        }
    }
}



void treeToPostfix(Tree* node, char postfixExp[]) {
    if (node == NULL)
        return;

    treeToPostfix(node->left, postfixExp);
    treeToPostfix(node->right, postfixExp);

    if (node->value.type == symb_NUMBER || node->value.type == symb_VAR) {
        char str[2] = {node->value.data.c, '\0'};
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    } else if (node->value.type == symb_OP) {
        char str[2] = {node->value.data.op, '\0'};
        strcat(postfixExp, " ");
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    }
}

void treeToExpresion(Tree* tree) {
    switch (tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf", tree->value.data.number);
            break;
        case symb_VAR:
            printf("%c", tree->value.data.c);
            break;
        case symb_OP:
            if (tree->value.data.op == OP_UNARY_MINUS) {
                printf("-");
                treeToExpresion(tree->right);
            } else {
                bool addParenthesesLeft = (tree->left->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->left->value.data.op));
                bool addParenthesesRight = (tree->right->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->right->value.data.op));

                if (tree->value.data.op == OP_DIVIDE && !addParenthesesLeft && !addParenthesesRight) {

                    addParenthesesLeft = (tree->left->value.type == symb_OP);
                    addParenthesesRight = (tree->right->value.type == symb_OP);
                }

                if (addParenthesesLeft) {
                    printf("(");
                }
                treeToExpresion(tree->left);
                if (addParenthesesLeft) {
                    printf(")");
                }

                printf("%c", oppToChar(tree->value.data.op));

                if (addParenthesesRight) {
                    printf("(");
                }
                treeToExpresion(tree->right);
                if (addParenthesesRight) {
                    printf(")");
                }
            }
            break;
        default:
            fprintf(stderr, "Ошибка, такого символа нет");
            return;
    }
}



int main(int argc, char const* argv[]) {

    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    stack* s1 = malloc(sizeof(stack));
    initStack(s1);
    char exp[MAX_EXPRESSION_LENGTH];

    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Не удалось прочитать данные из файла.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    node* expression = NULL;
    infixToPostfix(exp, &expression);
    Tree* tree = postfixToTree(expression);
    destroy(expression);
    printTree(tree, 0);
    printf("Упрощенное дерево выражений:\n");
    simplify_tree(tree, tree);


    while(tree->right == NULL){
        Tree* tmp = tree->left;
        tree->left->parent = NULL;           
        free(tree);
        tree = tmp;
        if (tree->left == NULL){
            break;
        }   
    }

    printTree(tree, 0);
    treeToExpresion(tree);
    printf("\n");
    clearTree(tree);
    stackDestroy(s1);
    return 0;
}