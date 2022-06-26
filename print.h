#ifndef PRINT_H_
#define PRINT_H_

#include <stdio.h>
#include "allocation.h"

void printResult(result_t *res) {
    printf("%d %d\n", res->node1, res->node2);
}

#endif