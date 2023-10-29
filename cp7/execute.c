#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

//Вариант [4,5] - два вектора, умножение вектора-строки на разреженную матрицу

int plusIndex(int col_num, int i, int j) { //функция создания индекса элемента матрицы
    return (i - 1) * col_num + (j - 1);
}


void print_vector(vector* v){
    printf("(size - %d) ", v->size);
    printf("Вектор: ");
    for(int i = 0; i < v->size; i++){
        printf("%d\t", v->value[i]);
    }
    printf("\n");
}


void printMatrix(vector* v, vector* vIndex, int row_num, int col_num) { //функция вывода матрицы


    int i = 1;
    int j = 1;
    int check = 0;
    int countNums = row_num * col_num; //количество элементов
    for (int k = 0; k < countNums; k++) {//цикл пока не вывели все элементы
        if (k % col_num == 0) {//если вывели всю строку, то печатаем перенос
            printf("\n");
        }        if (loadVector(vIndex, check) == plusIndex(col_num, i, j)) {//если индекс перебора совпал с индексом не нулевого элемента
            printf("%d\t", loadVector(v, check));//выводим его
            check++;//увеличиваем счетчик вывода таких элементов
       
        }
        else {
            printf("0\t");//печатаем ноль, так как матрица разряженна


        }
        if (j == col_num) {//если столбцы закончилась, то увеличиваем счетчик строк
            j = 0;//обнуляем счетчик столбцов
            i++;
        }
        j++;//увеличиваем счетчик прохода по столбцу
    }
    printf("\n");
}



void execute(vector* v, vector* vIndex, vector* vec_string, vector* string_Index, int string_length, int col_num){

    vector* resIndex = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* resValues = malloc(sizeof(vector));//выделяем память под вектор значений
    createVector(resIndex, col_num);//создаем эти векторы
    createVector(resValues, col_num);


    bool no_zero_res_elem = false;

    int counter = 0;

    for (int j = 1; j <= sizeVector(vIndex); j++) {
        int sum_res = 0;
        
        for (int k = 0; k < sizeVector(vIndex); k++){
            if((vIndex->value[k] % col_num + 1 == j)){
                int prove_j = vIndex->value[k] / col_num;;
                for (int l = 0; l < sizeVector(string_Index); l++){
                    if ((string_Index -> value[l]) % string_length == prove_j){
                        sum_res += (vec_string -> value[l]) * (v -> value[k]);
                        no_zero_res_elem = true;
                    }
                }
            }
        }   
        if (no_zero_res_elem){
            resIndex -> value[counter] = j - 1;
            resValues -> value[counter] = sum_res;
            counter++ ; 
        }
    }

    printMatrix(resValues, resIndex, 1, col_num);
    destroyVector(resIndex);//освобождаем память
    destroyVector(resValues);
    free(resIndex);
    free(resValues);
}


int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    vector* indexMatrix = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* valuesMatrix = malloc(sizeof(vector));//выделяем память под вектор значений

    vector* stringIndex = malloc(sizeof(vector));//выделяем память под вектор индексов строки
    vector* vec_string = malloc(sizeof(vector));//выделяем память под вектор значений строки
    int sizeRow;//количество строк
    int sizeColumn;//количество столбцов
    int sizeRow_str;//количество строк str
    int sizeColumn_str;//количество столбцов str

    FILE* input;//файл, с которым будем работать

    input = fopen(filename, "r");
    if (input == NULL) { // проверка на возможность открытия файла
        printf("Не удалось открыть файл!\n");
        return 1;
    }
 
    fscanf(input, "%d %d", &sizeRow_str, &sizeColumn_str);//считываем размер строки из файла

    createVector(vec_string, 1);
    createVector(stringIndex, 1);
    int indexRow_str = 1;
    int indexColumn_str = 1;
    int indexVector_str = 0;

    while (indexColumn_str <= sizeColumn_str) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(input, "%d", &scanNum);
        if (scanNum != 0) {
            
            writeVector(vec_string, indexVector_str, scanNum);
            resizeVector(vec_string, sizeVector(vec_string) + 1);
            writeVector(stringIndex, indexVector_str, plusIndex(sizeColumn_str, indexRow_str, indexColumn_str));
            resizeVector(stringIndex, sizeVector(stringIndex) + 1);
            indexVector_str++;

        }
        indexRow_str++;
        if (indexRow_str == sizeRow_str + 1) {
            indexColumn_str++;
            indexRow_str = 1;
        }
    }

    resizeVector(stringIndex, sizeVector(stringIndex) - 1);
    resizeVector(vec_string, sizeVector(vec_string) - 1);

    fscanf(input, "%d %d", &sizeRow, &sizeColumn);//считываем размер матрицы из файла

    createVector(indexMatrix, 1);
    createVector(valuesMatrix, 1);
    int indexRow = 1;
    int indexColumn = 1;
    int indexVector = 0;
    while (!feof(input)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(input, "%d", &scanNum);
        if (scanNum != 0) {
            writeVector(valuesMatrix, indexVector, scanNum);
            resizeVector(valuesMatrix, sizeVector(valuesMatrix) + 1);
            writeVector(indexMatrix, indexVector, plusIndex(sizeColumn, indexColumn, indexRow));
            resizeVector(indexMatrix, sizeVector(indexMatrix) + 1);
            indexVector++;

        }
        indexRow++;
        if (indexRow == sizeColumn + 1) {
            indexColumn++;
            indexRow = 1;
        }
    }

    resizeVector(indexMatrix, sizeVector(indexMatrix) - 1);
    resizeVector(valuesMatrix, sizeVector(valuesMatrix) - 1);


    fclose(input); //закрываем файл


    printf("\nИсходная строка равна:\n");
    printMatrix(vec_string, stringIndex, sizeRow_str, sizeColumn_str);

    printf("\nИсходная матрица равна:\n");
    printMatrix(valuesMatrix, indexMatrix, sizeRow, sizeColumn);

    printf("\nРезультат равен:\n");

    execute(valuesMatrix, indexMatrix, vec_string, stringIndex, sizeColumn_str, sizeColumn);

    free(indexMatrix);
    free(valuesMatrix);

    return 0;
}
