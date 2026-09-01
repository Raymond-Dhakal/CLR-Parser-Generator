#ifndef CLR_STATE_H
#define CLR_STATE_H

#include "grammar.h"
#include "closure.h"

typedef struct {
    int symbol;
    int target_state;
} Transition;

typedef struct {
    int id;
    ItemSet *items;
    Transition *transitions;
    int transition_count;
    int transition_capacity;
} State;

State *state_create(int id, ItemSet *items);
void state_destroy(State *state);

void state_add_transition(State *state, int symbol, int target);
int state_find_transition(const State *state, int symbol);

void state_print(const Grammar *g, const State *state);

#endif