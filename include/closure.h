#ifndef CLR_CLOSURE_H
#define CLR_CLOSURE_H

#include "grammar.h"
#include "first.h"
#include "lr1_item.h"

typedef struct {
    LR1Item *items;
    int count;
    int capacity;
} ItemSet;

ItemSet *itemset_create(void);
void itemset_destroy(ItemSet *set);

int itemset_add_item(ItemSet *set, LR1Item item);

ItemSet *itemset_copy(const ItemSet *set);
int itemset_equal(const ItemSet *a, const ItemSet *b);
void itemset_print(const Grammar *g, const ItemSet *set);

ItemSet *closure_compute(Grammar *g, const FirstSetsTable *first, const ItemSet *I);

#endif
