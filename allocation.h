#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include "error.h"
#include <stdlib.h>

typedef struct {
    int neighbors[3];
    int neighbors_num;
} node_t;

typedef struct {
    int node1;
    int node2;
    int diff;
} result_t;

#define N_ELEMS_IN_BEADT 4
#define MAXIMUM_N_NEIGHBRS 3
#define ALLOCATION_ERROR 1

node_t **allocateNodesNeighbors(int n_beads)
{
    node_t **neighbors = (node_t **)malloc(sizeof(node_t *) * n_beads);
    if (!neighbors) {
        exitError(ALLOCATION_ERROR);
    }
    for (int i = 0; i < n_beads; i++) {
        neighbors[i] = (node_t *)malloc(sizeof(node_t));
        if (!neighbors[i]) {
            exitError(ALLOCATION_ERROR);
        }
        neighbors[i]->neighbors_num = 0;
    }
    return neighbors;
}

int *allocateIntArray(int l)
{
    int *a = (int *)malloc(sizeof(int) * l);
    if (!a)
        exitError(ALLOCATION_ERROR);
    return a;
}

result_t *allocateResult()
{
    result_t *r = (result_t *)malloc(sizeof(result_t));
    if (!r) {
        exitError(ALLOCATION_ERROR);
    }
    r->diff = 0;
    return r;
}

void deallocateNodesNeighbors(node_t ***neighbors, int n_nodes)
{
    node_t *n = **neighbors;

    for (int i = 0; i < n_nodes; i++) {
        if (n + i * (sizeof(short)))
            free(n + i * (sizeof(short)));
    }
}

void deallocateIntArray(int **a)
{
    if (*a)
        free(*a);
}

void deallocateResult(result_t **res)
{
    if (*res)
        free(*res);
}

#endif