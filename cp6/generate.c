#include <stdio.h>
#include <stdlib.h>

#include "stud_comp.h"
#include "io.h"


int main(int argc, char *argv[]) 
{   
    if (argc != 3) {
        printf("Usage:\n\t%s FILE_FROM FILE_TO)\n", argv[0]);
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    stud_comp s;
    
        while(stud_comp_read_txt(&s, in)) {
            stud_comp_write_bin(&s, out);
            memset(&s, 0, sizeof(stud_comp));
        }
    fclose(in);
    fclose(out);

    return 0;
}


