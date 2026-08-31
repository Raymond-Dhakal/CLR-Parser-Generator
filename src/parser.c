#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef struct {
    int *data;
    int count;
    int capacity;
} IntStack;

static void stack_init(IntStack *s) {
    s->capacity = 64;
    s->data = (int *)malloc(sizeof(int) * s->capacity);
    s->count = 0;
}
static void stack_push(IntStack *s, int v) {
    if (s->count >= s->capacity) {
        s->capacity *= 2;
        s->data = (int *)realloc(s->data, sizeof(int) * s->capacity);
    }
    s->data[s->count++] = v;
}
static int stack_pop(IntStack *s) { return s->data[--s->count]; }
static int stack_top(const IntStack *s) { return s->data[s->count - 1]; }
static void stack_free(IntStack *s) { free(s->data); }

ParseResult parser_run(const Grammar *g, const ParsingTable *pt,
                        const int *input_tokens, int input_len, int verbose) {
    IntStack states, symbols;
    stack_init(&states);
    stack_init(&symbols);
    stack_push(&states, 0);

    int *buffer = (int *)malloc(sizeof(int) * (input_len + 1));
    for (int i = 0; i < input_len; i++) buffer[i] = input_tokens[i];
    buffer[input_len] = g->end_symbol;
    int ip = 0;
    int buf_len = input_len + 1;

    ParseResult result = PARSE_ERROR;

    if (verbose) {
        printf("%-30s %-30s %-20s %s\n", "STATE STACK", "SYMBOL STACK", "INPUT", "ACTION");
    }

    while (1) {
        int state = stack_top(&states);
        int lookahead = buffer[ip];
        ParsingAction action = pt->action[state][lookahead];

        if (verbose) {
            char state_buf[256] = {0}, sym_buf[256] = {0}, in_buf[256] = {0};
            char tmp[32];
            for (int i = 0; i < states.count; i++) { snprintf(tmp, sizeof(tmp), "%d ", states.data[i]); strncat(state_buf, tmp, sizeof(state_buf)-strlen(state_buf)-1); }
            for (int i = 0; i < symbols.count; i++) { snprintf(tmp, sizeof(tmp), "%s ", grammar_symbol_name(g, symbols.data[i])); strncat(sym_buf, tmp, sizeof(sym_buf)-strlen(sym_buf)-1); }
            for (int i = ip; i < buf_len; i++) { snprintf(tmp, sizeof(tmp), "%s ", grammar_symbol_name(g, buffer[i])); strncat(in_buf, tmp, sizeof(in_buf)-strlen(in_buf)-1); }
            printf("%-30s %-30s %-20s ", state_buf, sym_buf, in_buf);
        }

        if (action.type == ACTION_SHIFT) {
            if (verbose) printf("shift to I%d\n", action.value);
            stack_push(&symbols, lookahead);
            stack_push(&states, action.value);
            ip++;
        } else if (action.type == ACTION_REDUCE) {
            const Production *p = &g->productions[action.value];
            if (verbose) {
                printf("reduce by ");
                production_print(g, p);
                printf("\n");
            }
            for (int i = 0; i < p->rhs_len; i++) {
                stack_pop(&states);
                stack_pop(&symbols);
            }
            int prev_state = stack_top(&states);
            int goto_state = pt->go_to[prev_state][p->lhs];
            if (goto_state == -1) {
                fprintf(stderr, "parser_run: missing GOTO entry for state %d on %s\n",
                        prev_state, grammar_symbol_name(g, p->lhs));
                result = PARSE_ERROR;
                break;
            }
            stack_push(&symbols, p->lhs);
            stack_push(&states, goto_state);
        } else if (action.type == ACTION_ACCEPT) {
            if (verbose) printf("accept\n");
            result = PARSE_ACCEPT;
            break;
        } else {
            if (verbose) printf("ERROR\n");
            fprintf(stderr, "parser_run: syntax error in state %d on lookahead '%s' (input position %d)\n",
                    state, grammar_symbol_name(g, lookahead), ip);
            result = PARSE_ERROR;
            break;
        }
    }

    free(buffer);
    stack_free(&states);
    stack_free(&symbols);
    return result;
}