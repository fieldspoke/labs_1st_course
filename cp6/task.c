#include <stdio.h>
#include <stdlib.h>

#include "stud_comp.h"
#include "io.h"


/*

    Вариант №9: Составить список плохо сконфигурированных компьютеров.

    Поскольку в условии варианта не указано, какой конкретно компьютер считается "плохо сконфигурированным",
определим плохую конфигурацию для компьютера следующим образом.

    Назовём компьютер плохо сконфигурированным, когда для него выполняется одно из трёх условий:

    I. 
	1. Оперативная память <= 4 ГБ 
	2. Тип винчестера - HDD
	3. Тип процессора - x64

    II.
	1. Тип винчествера - HDD
	2. Суммарная ёмкость винчестверов (ёмкость одного * их количество ) <= 1000 ГБ
	3. Компьютер имеет < 8 внутренних контроллеров

    III.
	1. Тип видеоконтроллера - AGP
	2. Видеопамять - 2 ГБ
	3. Операционная сиситема - Ubuntu	

*/


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    stud_comp s;

    while (stud_comp_read_bin(&s, in)) {
        
        if  ( ((s.ram_size <= 4) && (!strcmp(s.proc_type, "x64")) && (!strcmp(s.hdd_type, "HDD")))  ||  ((!strcmp(s.hdd_type, "HDD")) && (s.hdd_num * s.hdd_cap < 1000) && (s.integr_contr_num < 8))  ||  ( !(strcmp(s.video_contr_type, "AGP")) && (s.video_mem_size == 2) && (!strcmp(s.op_system, "Ubuntu")))) {
            stud_comp_print(&s);
        }

    }

    fclose(in);

    return 0;
}