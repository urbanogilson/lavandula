#ifndef LAVENDER_PARSER_H
#define LAVENDER_PARSER_H

#include <stdbool.h>
#include "lavender_ast.h"
#include "lavender_lexer.h"

typedef struct {
    LavenderLexer *lexer;
    int           position;  // position in token array

    SchemaNode   *nodes;
    int           nodeCount;
    int           nodeCapacity;

    bool          hadError;
} LavenderParser;

// Parser functions
LavenderParser newParser(LavenderLexer *lexer);
void parseSchemaInternal(LavenderParser *parser);
void freeLavenderParser(LavenderParser *parser);

// Parser utility functions
bool expectToken(LavenderParser *parser, SchemaTokenType type);
SchemaNode parseModel(LavenderParser *parser);
SchemaNode parseSchemaStatement(LavenderParser *parser);
void createSchemaAst(LavenderParser *parser);

#endif