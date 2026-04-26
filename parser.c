#include "parser.h"

Grammar* create_grammar() {
    Grammar* g = (Grammar*)safe_malloc(sizeof(Grammar));
    g->symbol_count = 0;
    g->rule_count = 0;
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        g->symbol_table[i] = NULL;
        g->rules[i] = NULL;
    }
    return g;
}

int get_symbol_id(Grammar* g, const char* name) {
    for (int i = 0; i < g->symbol_count; i++) {
        if (strcmp(g->symbol_table[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int add_symbol(Grammar* g, const char* name) {
    int id = get_symbol_id(g, name);
    if (id != -1) return id;

    if (g->symbol_count >= MAX_SYMBOLS) {
        fprintf(stderr, "Error: Max symbols exceeded\n");
        return -1;
    }

    Symbol* s = (Symbol*)safe_malloc(sizeof(Symbol));
    s->name = duplicate_string(name);
    s->id = g->symbol_count;
    
    // In a universal parser, we don't assume Case. 
    // We will set is_non_terminal to 1 explicitly when it appears on LHS.
    s->is_non_terminal = 0; 

    g->symbol_table[g->symbol_count] = s;
    return g->symbol_count++;
}

void parse_line(Grammar* g, char* line) {
    const char* arrows[] = { "::=", "->", ":=", "=" };
    char* arrow_pos = NULL;
    int arrow_len = 0;

    // Detect which assignment operator is used
    for (int i = 0; i < 4; i++) {
        arrow_pos = strstr(line, arrows[i]);
        if (arrow_pos) {
            arrow_len = strlen(arrows[i]);
            break;
        }
    }

    if (!arrow_pos) return;

    *arrow_pos = '\0';
    char* lhs_str = trim_whitespace(line);
    char* rhs_str = arrow_pos + arrow_len;

    int lhs_id = add_symbol(g, lhs_str);
    g->symbol_table[lhs_id]->is_non_terminal = 1;

    Rule* r = (Rule*)safe_malloc(sizeof(Rule));
    r->lhs_id = lhs_id;
    r->alt_count = 0;

    // Split RHS by |
    char* next_alt = rhs_str;
    while (next_alt && r->alt_count < MAX_ALTERNATIVES) {
        char* current_alt = next_alt;
        char* pipe = strchr(current_alt, '|');
        if (pipe) {
            *pipe = '\0';
            next_alt = pipe + 1;
        } else {
            next_alt = NULL;
        }

        char* trimmed_alt = trim_whitespace(current_alt);
        if (strlen(trimmed_alt) > 0) {
            // Extract first token of alternative
            char* first_token = trimmed_alt;
            char* space = strpbrk(trimmed_alt, " \t"); // Handle tabs too
            if (space) *space = '\0';
            
            r->first_symbol_ids[r->alt_count++] = add_symbol(g, first_token);
        }
    }

    g->rules[g->rule_count++] = r;
}

void free_grammar(Grammar* g) {
    if (!g) return;
    for (int i = 0; i < g->symbol_count; i++) {
        if (g->symbol_table[i]) {
            free(g->symbol_table[i]->name);
            free(g->symbol_table[i]);
        }
    }
    for (int i = 0; i < g->rule_count; i++) {
        if (g->rules[i]) free(g->rules[i]);
    }
    free(g);
}
