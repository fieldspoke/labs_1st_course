#include "vector.h"


// Вариант [8,5] - турнирная сортировка, тип ключа - double

// Функция записи вектора в файл
void rewriteFile(const char* filename, vector* table) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open the file for writing.\n");
        return;
    }

    int size_of_Table = sizeV(table);

    // Записываем каждый элемент вектора в файл
    for (int i = 0; i < size_of_Table; i++) {
        value tmp = load(table, i);
        fprintf(file, "%lf %s\n", tmp.key, tmp.string);
    }

    fclose(file);
}

int main(int argc, char const* argv[]) {
    // Проверка наличия аргумента командной строки (имени файла)
    if (argc != 2) {
        printf("Use: %s <filename>\n", argv[0]);
        return 1;
    }

    // Открытие файла для чтения
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    // Создание и инициализация вектора
    vector* table = malloc(sizeof(vector));
    create(table, 0);

    char line[STRSIZE];

    // Считывание данных из файла и добавление их в вектор
    while (fgets(line, sizeof(line), file) != NULL) {
        double key;
        char string[STRSIZE];
        sscanf(line, "%lf %[^\n]", &key, string);

        value element;
        element.key = key;
        strcpy(element.string, string);
        resize(table, sizeV(table) + 1);
        write(table, sizeV(table) - 1, element);
    }

    fclose(file);

    printf("The original table looks like this:\n");
    printT(table);
    int choice;
    double key;

    // Цикл обработки пользовательских действий
    while (1) {
        printf("\n Select an action:\n");
        printf("1. Print the table\n");
        printf("2. Sort the table\n");
        printf("3. Find a string by key\n");
        printf("4. Overwrite the file\n");
        printf("5. Exit\n");
        printf("Enter the action number: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("The action 'Print the table' was selected\n");
                printT(table);
                break;
            case 2:
                printf("The action 'Sort the table' was selected\n");
                tournamentSort(table);
                printf("The table is sorted:\n");
                printT(table);
                break;
            case 3:
                printf("The action 'Find a string by key' was selected\n");
                // Проверка типа сортировки и вызов соответствующей функции поиска
                if (getSortTable(table) == descending) {
                    printf("Enter the key: ");
                    scanf("%lf", &key);
                    value result = reverseBinarySearch(table, key);
                    if (result.key != 0) {
                        printf("| %12lf | %s |\n", result.key, result.string);
                    } else {
                        printf("The specified key is not in the table\n");
                    }
                    break;
                } else if (getSortTable(table) == unsorted) {
                    printf("To start, sort the table!\n");
                    break;
                } else {
                    printf("Enter the key: ");
                    scanf("%lf", &key);
                    value result = binarySearch(table, key);
                    if (result.key != 0) {
                        printf("| %12lf | %s |\n", result.key, result.string);
                    } else {
                        printf("The specified key is not in the table\n");
                    }
                    break;
                }
            case 4:
                printf("The action 'Overwrite the file' was selected\n");
                // Запись вектора в файл
                rewriteFile(argv[1], table);
                printf("The file has been successfully overwritten!\n");
                break;
            case 5:
                printf("The action 'Exit' was selected\n");
                destroy(table);
                free(table);
                return 0;
            default:
                printf("The specified action does not exist!\n");
                break;
        }
    }
    destroy(table);
    return 0;
}
