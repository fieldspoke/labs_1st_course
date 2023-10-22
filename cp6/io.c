#include <stdio.h>
#include <stdlib.h>

#include "stud_comp.h"
#include "io.h"

/* stud_comp IO */

int stud_comp_read_txt(stud_comp *s, FILE *in)
{
    fscanf(in, "%s", s->stud_surname);
    fscanf(in, "%d", &(s->proc_num));
    fscanf(in, "%s", s->proc_type);
    fscanf(in, "%d", &(s->ram_size));
    fscanf(in, "%s", s->video_contr_type);
    fscanf(in, "%d", &(s->video_mem_size));
    fscanf(in, "%s", s->hdd_type);
    fscanf(in, "%d", &(s->hdd_num));
    fscanf(in, "%d", &(s->hdd_cap));
    fscanf(in, "%d", &(s->integr_contr_num));
    fscanf(in, "%d", &(s->device_num));
    fscanf(in, "%s", s->op_system);

    return !feof(in);
}

int stud_comp_read_bin(stud_comp *s, FILE *in)
{
    fread(s->stud_surname,  sizeof(char), STR_SIZE, in);
    fread(&(s->proc_num), sizeof(int), 1, in);
    fread(s->proc_type, sizeof(char), STR_SIZE, in);
    fread(&(s->ram_size), sizeof(int), 1, in);
    fread(s->video_contr_type, sizeof(char), STR_SIZE, in);
    fread(&(s->video_mem_size), sizeof(int), 1, in);
    fread(s->hdd_type, sizeof(char), STR_SIZE, in);
    fread(&(s->hdd_num), sizeof(int), 1, in);
    fread(&(s->hdd_cap), sizeof(int), 1, in);
    fread(&(s->integr_contr_num), sizeof(int), 1, in);
    fread(&(s->device_num), sizeof(int), 1, in);
    fread(s->op_system, sizeof(char), STR_SIZE, in);

    return !feof(in);
}

void stud_comp_write_bin(stud_comp *s, FILE *out)
{

    fwrite(s->stud_surname,  sizeof(char), STR_SIZE, out);
    fwrite(&(s->proc_num), sizeof(int), 1, out);
    fwrite(s->proc_type, sizeof(char), STR_SIZE, out);
    fwrite(&(s->ram_size), sizeof(int), 1, out);
    fwrite(s->video_contr_type, sizeof(char), STR_SIZE, out);
    fwrite(&(s->video_mem_size), sizeof(int), 1, out);
    fwrite(s->hdd_type, sizeof(char), STR_SIZE, out);
    fwrite(&(s->hdd_num), sizeof(int), 1, out);
    fwrite(&(s->hdd_cap), sizeof(int), 1, out);
    fwrite(&(s->integr_contr_num), sizeof(int), 1, out);
    fwrite(&(s->device_num), sizeof(int), 1, out);
    fwrite(s->op_system, sizeof(char), STR_SIZE, out);
}

void stud_comp_print(stud_comp *s)
{
    printf("Фамилия студента: %s\n", s->stud_surname);
    printf("Количество процессоров: %d\n", s->proc_num);
    printf("Тип процессоров: %s\n", s->proc_type);
    printf("Размер оперативной памяти: %d\n", s->ram_size);
    printf("Тип видеоконтроллера: %s\n", s->video_contr_type);
    printf("Объем видеопамяти: %d\n", s->video_mem_size);
    printf("Тип винчестера: %s\n", s->hdd_type);
    printf("Количество винчестеров: %d\n", s->hdd_num);
    printf("Емкость винчестеров: %d\n", s->hdd_cap);
    printf("Количество интегрированных контроллеров: %d\n", s->integr_contr_num);
    printf("Количество внешних устройств: %d\n", s->device_num);
    printf("Операционная система: %s\n", s->op_system);

    printf("\n");
}