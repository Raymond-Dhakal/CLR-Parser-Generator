#ifndef CLR_LR1_ITEM_H
#define CLR_LR1_ITEM_H

#include "grammar.h"

typedef struct {
    int production_id;
    int dot_pos;
    int lookahead;
} LR1Item;

LR1Item lr1_item_create(int production_id, int dot_pos, int lookahead);
int lr1_item_equal(const LR1Item *a, const LR1Item *b);
int lr1_item_core_equal(const LR1Item *a, const LR1Item *b);
LR1Item lr1_item_copy(const LR1Item *item);

int lr1_item_dot_symbol(const Grammar *g, const LR1Item *item);

int lr1_item_is_complete(const Grammar *g, const LR1Item *item);

void lr1_item_print(const Grammar *g, const LR1Item *item);

#endif
