#ifndef GRAPH_H
#define GRAPH_H

#include "parser.h"

typedef struct {
    int num_nodes;
    int** adj;
    int* adj_size;
} Graph;

/**
 * @brief Builds a dependency graph from the grammar.
 * An edge A -> B exists if B appears as the first symbol in any production of A.
 */
Graph* build_graph(Grammar* g);

/**
 * @brief Frees graph memory.
 */
void free_graph(Graph* g);

#endif
