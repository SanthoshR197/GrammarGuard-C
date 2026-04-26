#include <stdio.h>
#include "parser.h"
#include "graph.h"
#include "recursion.h"

int main(int argc, char* argv[]) {
    FILE* file;
    
    if (argc < 2) {
        // Switch to Interactive Terminal Mode
        file = stdin;
        printf("--- Left Recursion Detector: Interactive Mode ---\n");
        printf("Enter grammar rules (e.g., A -> B | c)\n");
        printf("Press Ctrl+Z then Enter (Windows) or Ctrl+D (Linux) to analyze:\n\n");
    } else {
        file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
    }

    Grammar* g = create_grammar();
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline and carriage return
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) > 0) {
            parse_line(g, line);
        }
    }
    
    if (file != stdin) fclose(file);

    if (g->symbol_count == 0) {
        printf("No valid grammar rules found.\n");
        free_grammar(g);
        return 0;
    }

    Graph* gr = build_graph(g);

    printf("--- Left Recursion Risk Detection Report ---\n\n");

    // We analyze every symbol that was identified as a non-terminal
    for (int i = 0; i < g->symbol_count; i++) {
        if (!g->symbol_table[i]->is_non_terminal) continue;

        RecursionResult res = analyze_node(gr, i);
        
        printf("NonTerminal: %s\n", g->symbol_table[i]->name);
        printf("Has_Left_Recursion: %d\n", res.has_left_recursion);
        
        const char* type_str = "None";
        if (res.type == REC_DIRECT) type_str = "Direct";
        else if (res.type == REC_INDIRECT) type_str = "Indirect";
        
        printf("Type: %s\n", type_str);
        printf("Recursion_Depth: %d\n\n", res.depth);
    }

    // Cleanup
    free_graph(gr);
    free_grammar(g);

    return 0;
}
