#ifndef CLR_FIRST_H
#define CLR_FIRST_H

#include "grammar.h"

typedef struct {
    int *symbols;
    int count;
    int capacity;
} SymbolSet;

typedef struct {
    Grammar *grammar;
    SymbolSet *first_sets;
    int *nullable;
} FirstSetsTable;

void symbolset_init(SymbolSet *s);
void symbolset_free(SymbolSet *s);
int symbolset_add(SymbolSet *s, int sym);
int symbolset_contains(const SymbolSet *s, int sym);
void symbolset_union(SymbolSet *dst, const SymbolSet *src);

FirstSetsTable *first_sets_compute(Grammar *g);
void first_sets_destroy(FirstSetsTable *t);

SymbolSet first_of_sequence(const FirstSetsTable *t, const int *seq, int len,
                             int trailing_lookahead);

void first_sets_print(const Grammar *g, const FirstSetsTable *t);

#endif