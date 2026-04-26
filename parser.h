#ifndef PARSER_H
#define PARSER_H

#include "utils.h"

#define MAX_SYMBOLS 100
#define MAX_ALTERNATIVES 20

typedef struct {
    char* name;
    int id;
    int is_non_terminal; // 1 if it appears on the LHS of any rule
} Symbol;

typedef struct {
    int lhs_id;
    int first_symbol_ids[MAX_ALTERNATIVES]; // IDs of symbols at the start of each alternative
    int alt_count;
} Rule;

typedef struct {
    Symbol* symbol_table[MAX_SYMBOLS];
    int symbol_count;
    Rule* rules[MAX_SYMBOLS];
    int rule_count;
} Grammar;

Grammar* create_grammar();
int get_symbol_id(Grammar* g, const char* name);
int add_symbol(Grammar* g, const char* name);
void parse_line(Grammar* g, char* line);
void free_grammar(Grammar* g);

#endif
