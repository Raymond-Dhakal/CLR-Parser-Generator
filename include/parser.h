#ifndef CLR_PARSER_H
#define CLR_PARSER_H

#include "grammar.h"
#include "parsing_table.h"

typedef enum {
    PARSE_ACCEPT,
    PARSE_ERROR
} ParseResult;

ParseResult parser_run(const Grammar *g, const ParsingTable *pt,
                        const int *input_tokens, int input_len, int verbose);

#endif