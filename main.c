#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "allocation.h"
#include "print.h"
#include "read.h"

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)

#define OFFSET(x) (x - 1)

#define NO_PREVIOUS 0
#define ROOT_NODE 1

int nodes_num, red_nodes_num;
#define NODE_IS_RED(node) (node <= red_nodes_num)
result_t *result;

#define REPLACE_CONDITION(new_diff, new_node1, new_node2)                      \
    (new_diff < result->diff ||                                                \
     (new_node1 == result->node1 && new_node2 < result->node2))

node_t **loadEdges(int beads);
int getNumOfRed(int node, node_t **neighbors, int *reds_u_nodes, int prev_node);
void findSolution(int node, node_t **neighbors, int *reds_u_nodes,
                  int prev_node);
void cleanUp(node_t **neighbors, int *reds_u_nodes);

int main(int argc, char *argv[])
{
    int ret = 0;

    readTwoInts(&nodes_num, &red_nodes_num);

    node_t **neighbors = loadEdges(nodes_num);

    int *reds_under_nodes = allocateIntArray(nodes_num);
    int tmp = getNumOfRed(ROOT_NODE, neighbors, reds_under_nodes, NO_PREVIOUS);

    result = allocateResult();

    findSolution(ROOT_NODE, neighbors, reds_under_nodes, NO_PREVIOUS);
    printResult(result);

    cleanUp(neighbors, reds_under_nodes);
    return ret;
}

node_t **loadEdges(int nodes)
{
    node_t **beads_neighbors = allocateNodesNeighbors(nodes);

    int left_node, right_node;

    for (int edge = 0; edge < nodes - 1; edge++) {

        readTwoInts(&left_node, &right_node);

        node_t *current_left = beads_neighbors[OFFSET(left_node)];
        current_left->neighbors[current_left->neighbors_num] = right_node;
        current_left->neighbors_num += 1;

        node_t *current_right = beads_neighbors[OFFSET(right_node)];
        current_right->neighbors[current_right->neighbors_num] = left_node;
        current_right->neighbors_num += 1;
    }

    return beads_neighbors;
}

int getNumOfRed(int node, node_t **neighbors, int *reds_u_nodes, int prev_node)
{
    int reds_under_node = 0;
    node_t *current = neighbors[OFFSET(node)];
    for (int i = 0; i < current->neighbors_num; i++) {

        if (current->neighbors[i] != prev_node) {
            reds_under_node +=
                NODE_IS_RED(current->neighbors[i])
                    ? getNumOfRed(current->neighbors[i], neighbors,
                                  reds_u_nodes, node) +
                          1
                    : getNumOfRed(current->neighbors[i], neighbors,
                                  reds_u_nodes, node);
        }
    }

    reds_u_nodes[OFFSET(node)] =
        NODE_IS_RED(node) ? reds_under_node + 1 : reds_under_node;

    return reds_under_node;
}

void findSolution(int node, node_t **neighbors, int *reds_u_nodes,
                  int prev_node)
{
    node_t *current = neighbors[OFFSET(node)];

    for (int i = 0; i < current->neighbors_num; i++) {

        if (current->neighbors[i] != prev_node) {

            int reds_under_node = reds_u_nodes[OFFSET(current->neighbors[i])];
            int node1 = MIN(node, current->neighbors[i]);
            int node2 = MAX(node, current->neighbors[i]);
            int diff = abs(2 * reds_under_node - red_nodes_num);

            if (node == 1 && i == 0) {
                result->node1 = node1;
                result->node2 = node2;
                result->diff = diff;

            } else {

                if (REPLACE_CONDITION(diff, node1, node2)) {
                    result->node1 = node1;
                    result->node2 = node2;
                    result->diff = diff;
                }
            }
            findSolution(current->neighbors[i], neighbors, reds_u_nodes, node);
        }
    }
}

void cleanUp(node_t **neighbors, int *reds_u_nodes)
{
    deallocateNodesNeighbors(&neighbors, nodes_num);
    deallocateIntArray(&reds_u_nodes);
    deallocateResult(&result);
}