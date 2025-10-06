#ifndef LAVENDER_PARSER_H
#define LAVENDER_PARSER_H

#include <stdbool.h>
#include "lavender_ast.h"
#include "lavender_lexer.h"

typedef struct {
    LavenderLexer *lexer;
    int           position;

    SchemaNode   *nodes;
    int           nodeCount;
    int           nodeCapacity;

    bool          hadError;
} LavenderParser;

LavenderParser newParser(LavenderLexer *lexer);
void freeLavenderParser(LavenderParser *parser);

void parseSchemaInternal(LavenderParser *parser);

#endif