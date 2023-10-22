#ifndef _IO_H_
#define _IO_H_

#include "stud_comp.h"

/* stud_comp IO */
int  stud_comp_read_txt(stud_comp *s, FILE *in);
int  stud_comp_read_bin(stud_comp *s, FILE *in);
void stud_comp_write_bin(stud_comp *s, FILE *out);
void stud_comp_print(stud_comp *s);

#endif