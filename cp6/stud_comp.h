#ifndef _STUD_COMP_H_
#define _STUD_COMP_H_

#define STR_SIZE 30

typedef struct
{
    char stud_surname[STR_SIZE]; // Фамилия студента
    int proc_num; // Количество процессоров
    char proc_type[STR_SIZE]; // Тип процесоров
    int ram_size; // Размер оперативной памяти
    char video_contr_type[STR_SIZE]; // Тип видеоконтроллера
    int video_mem_size; // Объем видеопамяти
    char hdd_type[STR_SIZE]; // Тип винчестера
    int hdd_num; // Количество винчестеров
    int hdd_cap; // Емкость винчестеров
    int integr_contr_num; // Количество интегрированных контроллеров
    int device_num; // Количество внешних устройств 
    char op_system[STR_SIZE]; // Операционная система
} stud_comp;

#endif