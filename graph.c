#include "graph.h"

Graph* build_graph(Grammar* g) {
    Graph* gr = (Graph*)safe_malloc(sizeof(Graph));
    gr->num_nodes = g->symbol_count;
    gr->adj = (int**)safe_malloc(sizeof(int*) * gr->num_nodes);
    gr->adj_size = (int*)safe_malloc(sizeof(int) * gr->num_nodes);

    for (int i = 0; i < gr->num_nodes; i++) {
        gr->adj[i] = (int*)safe_malloc(sizeof(int) * MAX_ALTERNATIVES);
        gr->adj_size[i] = 0;
    }

    // Populate graph based on grammar rules
    for (int i = 0; i < g->rule_count; i++) {
        Rule* r = g->rules[i];
        if (!r) continue;
        int u = r->lhs_id;
        
        for (int j = 0; j < r->alt_count; j++) {
            int v = r->first_symbol_ids[j];
            
            // We only care about edges between non-terminals for left recursion
            if (g->symbol_table[v]->is_non_terminal) {
                // Check for duplicate edges to keep graph clean
                int exists = 0;
                for(int k = 0; k < gr->adj_size[u]; k++) {
                    if (gr->adj[u][k] == v) {
                        exists = 1;
                        break;
                    }
                }
                
                if (!exists) {
                    gr->adj[u][gr->adj_size[u]++] = v;
                }
            }
        }
    }

    return gr;
}

void free_graph(Graph* gr) {
    if (!gr) return;
    for (int i = 0; i < gr->num_nodes; i++) {
        free(gr->adj[i]);
    }
    free(gr->adj);
    free(gr->adj_size);
    free(gr);
}
