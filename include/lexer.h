#ifndef CLR_LEXER_H
#define CLR_LEXER_H

#include "grammar.h"

typedef struct {
    int *tokens;
    int count;
    int capacity;
} TokenStream;

TokenStream *lexer_tokenize(const Grammar *g, const char *input_line);
void lexer_destroy(TokenStream *ts);
void lexer_print(const Grammar *g, const TokenStream *ts);

#endif
