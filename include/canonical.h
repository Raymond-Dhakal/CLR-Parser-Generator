#ifndef CLR_CANONICAL_H
#define CLR_CANONICAL_H

#include "grammar.h"
#include "first.h"
#include "state.h"

typedef struct {
    State **states;
    int count;
    int capacity;
    Grammar *grammar;
    const FirstSetsTable *first;
} CanonicalCollection;

CanonicalCollection *canonical_build(Grammar *g, const FirstSetsTable *first);
void canonical_destroy(CanonicalCollection *c);
void canonical_print(const CanonicalCollection *c);

#endif