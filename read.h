#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include "error.h"

#define INPUT_ERROR 0

void readTwoInts(int *frst, int *scnd) 
{
    if (scanf("%d %d\r", frst, scnd) != 2) {
        exitError(INPUT_ERROR);
    }
}

#endif