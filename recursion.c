#include "recursion.h"

/**
 * @brief Helper function to perform DFS and find the maximum path length back to start_node.
 */
void dfs_find_max_cycle(Graph* gr, int current, int target, int* visited, int current_depth, int* max_depth) {
    for (int i = 0; i < gr->adj_size[current]; i++) {
        int neighbor = gr->adj[current][i];
        
        if (neighbor == target) {
            // Found a cycle back to the target node
            if (current_depth + 1 > *max_depth) {
                *max_depth = current_depth + 1;
            }
        } else if (!visited[neighbor]) {
            visited[neighbor] = 1;
            dfs_find_max_cycle(gr, neighbor, target, visited, current_depth + 1, max_depth);
            visited[neighbor] = 0; // Backtrack
        }
    }
}

RecursionResult analyze_node(Graph* gr, int u) {
    RecursionResult res;
    res.has_left_recursion = 0;
    res.type = REC_NONE;
    res.depth = 0;

    // 1. Check for Direct Left Recursion (Self-loop)
    for (int i = 0; i < gr->adj_size[u]; i++) {
        if (gr->adj[u][i] == u) {
            res.has_left_recursion = 1;
            res.type = REC_DIRECT;
            res.depth = 1;
            // Note: Even if it has indirect, Direct is usually prioritized in classification
            // or we could say it's both. The requirement implies one classification.
            return res;
        }
    }

    // 2. Check for Indirect Left Recursion
    int max_depth = 0;
    int* visited = (int*)calloc(gr->num_nodes, sizeof(int));
    if (!visited) return res;

    // We don't mark start node as visited initially to allow finding a path back to it
    dfs_find_max_cycle(gr, u, u, visited, 0, &max_depth);
    
    free(visited);

    if (max_depth > 0) {
        res.has_left_recursion = 1;
        res.type = (max_depth == 1) ? REC_DIRECT : REC_INDIRECT;
        res.depth = max_depth;
    }

    return res;
}
