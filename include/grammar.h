#ifndef CLR_GRAMMAR_H
#define CLR_GRAMMAR_H

#define MAX_NAME_LEN 64
#define EPSILON_NAME "EPSILON"
#define END_NAME "$"

typedef enum {
    SYM_TERMINAL,
    SYM_NONTERMINAL,
    SYM_EPSILON,
    SYM_END,
    SYM_UNKNOWN
} SymbolType;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    SymbolType type;
} Symbol;

typedef struct {
    int id;
    int lhs;
    int *rhs;
    int rhs_len;
} Production;

typedef struct {
    Symbol *symbols;
    int symbol_count;
    int symbol_capacity;

    Production *productions;
    int production_count;
    int production_capacity;

    int start_symbol;
    int augmented_start;
    int augmented_production;

    int epsilon_symbol;
    int end_symbol;
} Grammar;

Grammar *grammar_create(void);
void grammar_destroy(Grammar *g);

int grammar_add_symbol(Grammar *g, const char *name, SymbolType type);
int grammar_find_symbol(const Grammar *g, const char *name);

int grammar_add_production(Grammar *g, int lhs, int *rhs, int rhs_len);

int grammar_load_from_file(Grammar *g, const char *filename);
void grammar_augment(Grammar *g);

int grammar_is_terminal(const Grammar *g, int sym_id);
int grammar_is_nonterminal(const Grammar *g, int sym_id);
int grammar_is_epsilon(const Grammar *g, int sym_id);
int grammar_is_end(const Grammar *g, int sym_id);
const char *grammar_symbol_name(const Grammar *g, int sym_id);

void grammar_print(const Grammar *g);
void production_print(const Grammar *g, const Production *p);

#endif