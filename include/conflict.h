#ifndef CLR_CONFLICT_H
#define CLR_CONFLICT_H

#include "grammar.h"

typedef enum {
    ACTION_NONE,
    ACTION_SHIFT,
    ACTION_REDUCE,
    ACTION_ACCEPT,
    ACTION_ERROR
} ActionType;

typedef struct {
    ActionType type;
    int value;
} ParsingAction;

typedef enum {
    CONFLICT_SHIFT_REDUCE,
    CONFLICT_REDUCE_REDUCE
} ConflictType;

typedef struct {
    ConflictType type;
    int state;
    int symbol;
    ParsingAction existing;
    ParsingAction attempted;
} Conflict;

typedef struct {
    Conflict *items;
    int count;
    int capacity;
} ConflictList;

ConflictList *conflict_list_create(void);
void conflict_list_destroy(ConflictList *list);
void conflict_list_add(ConflictList *list, Conflict c);
void conflict_list_print(const Grammar *g, const ConflictList *list);

#endif