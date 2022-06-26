#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>

#define ERROR 1

char errors[2][100] = {"Wrong arguments provided!",
                       "Error during dynamic allocation!"};

void exitError(int error_num)
{
    fprintf(stderr, "Error: %s\n", errors[error_num]);
    exit(ERROR);
}

#endif