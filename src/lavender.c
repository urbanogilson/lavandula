#include <stdlib.h>
#include "include/lavender.h"

LavenderSchemaParser newSchemaParser(const char *source) {
    LavenderLexer *lexer = malloc(sizeof(LavenderLexer));
    *lexer = newLexer(source);
    
    LavenderParser *parser = malloc(sizeof(LavenderParser));
    *parser = newParser(lexer);

    LavenderSchemaParser schemaParser = {
        .source = source,
        .lexer = lexer,
        .parser = parser,
        .hadError = false,
    };

    return schemaParser;
}

void parseSchema(LavenderSchemaParser *schemaParser) {
    parseSchemaInternal(schemaParser->parser);
    schemaParser->hadError = schemaParser->parser->hadError;
}

void freeSchemaParser(LavenderSchemaParser *schemaParser) {
    if (!schemaParser) return;

    if (schemaParser->parser) {
        freeLavenderParser(schemaParser->parser);
        free(schemaParser->parser);
    }

    if (schemaParser->lexer) {
        freeLexer(schemaParser->lexer);
        free(schemaParser->lexer);
    }
}