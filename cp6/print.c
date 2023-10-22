#include <stdio.h>
#include <stdlib.h>

#include "stud_comp.h"
#include "io.h"


int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");

    if (argc != 2) {
        printf("Usage:\n\t./print DB_FILE\n");
        exit(0);
    }

    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    stud_comp s;

    while (stud_comp_read_bin(&s, in)) {
        stud_comp_print(&s); 
    }

    fclose(in);

    return 0;
}
