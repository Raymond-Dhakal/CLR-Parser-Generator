#ifndef CLR_GOTO_H
#define CLR_GOTO_H

#include "grammar.h"
#include "first.h"
#include "closure.h"

ItemSet *goto_compute(Grammar *g, const FirstSetsTable *first,
                       const ItemSet *I, int symbol);

#endif
