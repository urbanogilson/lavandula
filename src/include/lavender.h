#ifndef LAVENDER_H
#define LAVENDER_H

#include <stdbool.h>

#include "lavender_ast.h"
#include "lavender_lexer.h"
#include "lavender_parser.h"
#include "lavender_transpiler.h"

typedef struct {
    const char         *source;
    LavenderLexer      *lexer;
    LavenderParser     *parser;
    LavenderTranspiler *transpiler;

    bool                hadError;
} LavenderSchemaParser;

LavenderSchemaParser newSchemaParser(const char *source);

void parseSchema(LavenderSchemaParser *parser);
void freeSchemaParser(LavenderSchemaParser *parser);

#endif