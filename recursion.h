#ifndef RECURSION_H
#define RECURSION_H

#include "graph.h"

typedef enum {
    REC_NONE = 0,
    REC_DIRECT = 1,
    REC_INDIRECT = 2
} RecursionType;

typedef struct {
    int has_left_recursion;
    RecursionType type;
    int depth;
} RecursionResult;

/**
 * @brief Analyzes a specific non-terminal for left recursion.
 */
RecursionResult analyze_node(Graph* gr, int start_node);

#endif
