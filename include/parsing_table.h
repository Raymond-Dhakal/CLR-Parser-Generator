#ifndef CLR_PARSING_TABLE_H
#define CLR_PARSING_TABLE_H

#include "grammar.h"
#include "canonical.h"
#include "conflict.h"

typedef struct {
    const Grammar *grammar;
    int num_states;
    int num_symbols;
    ParsingAction **action;
    int **go_to;
} ParsingTable;

ParsingTable *parsing_table_build(const Grammar *g, const CanonicalCollection *cc,
                                   ConflictList *conflicts);
void parsing_table_destroy(ParsingTable *pt);
void parsing_table_print(const ParsingTable *pt);

#endif