#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/lavender_parser.h"

static bool isLast(LavenderParser *parser) {
    return parser->position >= parser->lexer->tokenCount;
}

static void advance(LavenderParser *parser) {
    parser->position++;
}

static SchemaNode badNode(LavenderParser *parser) {
    parser->hadError = true;

    SchemaNode node = {
        .type = -1,
    };

    return node;
}

bool expectToken(LavenderParser *parser, SchemaTokenType type) {
    if (isLast(parser)) return false;

    SchemaToken token = parser->lexer->tokens[parser->position];
    if (token.type != type) return false;

    advance(parser);
    return true;
}

SchemaNode parseModel(LavenderParser *parser) {
    advance(parser);
    if (isLast(parser)) {
        return badNode(parser);
    }

    SchemaToken nameToken = parser->lexer->tokens[parser->position];
    if (nameToken.type != SCHEMA_TOKEN_IDENTIFIER) {
        printf("Expected model name after 'model', got: %s\n", nameToken.lexeme);
        return badNode(parser);
    }
    advance(parser);

    if (!expectToken(parser, SCHEMA_TOKEN_LBRACE)) {
        printf("Expected '{' after model name, got: %s\n", parser->lexer->tokens[parser->position].lexeme);
        return badNode(parser);
    }

    if (!expectToken(parser, SCHEMA_TOKEN_RBRACE)) {
        printf("Expected '}' after model name, got: %s\n", parser->lexer->tokens[parser->position].lexeme);
        return badNode(parser);
    }

    ModelDeclaration model = {
        .name = strdup(nameToken.lexeme),
    };

    SchemaNode node = {
        .type = SCHEMA_NODE_MODEL,
        .model = model,
    };

    return node;
}

SchemaNode parseSchemaStatement(LavenderParser *parser) {
    SchemaToken token = parser->lexer->tokens[parser->position];

    switch (token.type) {
        case SCHEMA_TOKEN_MODEL:
            return parseModel(parser);
        default:
            parser->hadError = true;
            printf("Unexpected token: %s\n", token.lexeme);
            exit(1);
    }
}

void createSchemaAst(LavenderParser *parser) {
    parser->position = 0;

    while (!isLast(parser)) {
        SchemaNode node = parseSchemaStatement(parser);
        if (parser->hadError) return;

        if (parser->nodeCount >= parser->nodeCapacity) {
            parser->nodeCapacity *= 2;
            parser->nodes = realloc(parser->nodes, sizeof(SchemaNode) * parser->nodeCapacity);
        }

        parser->nodes[parser->nodeCount++] = node;
    }
}

void parseSchemaInternal(LavenderParser *parser) {
    tokenizeSchema(parser->lexer);
    if (parser->lexer->hadError) {
        parser->hadError = true;
        return;
    }

    for (int i = 0; i < parser->lexer->tokenCount; i++) {
        printToken(&parser->lexer->tokens[i]);
    }

    createSchemaAst(parser);
    if (parser->hadError) return;

    for (int i = 0; i < parser->nodeCount; i++) {
        printSchemaNode(&parser->nodes[i]);
    }
}

LavenderParser newParser(LavenderLexer *lexer) {
    LavenderParser parser = {
        .lexer = lexer,
        .position = 0,
        .nodes = malloc(sizeof(SchemaNode)),
        .nodeCount = 0,
        .nodeCapacity = 1,
        .hadError = false,
    };

    return parser;
}

void freeLavenderParser(LavenderParser *parser) {
    if (!parser) return;

    for (int i = 0; i < parser->nodeCount; i++) {
        freeSchemaNode(&parser->nodes[i]);
    }

    free(parser->nodes);
    parser->nodes = NULL;
    parser->nodeCount = 0;
    parser->nodeCapacity = 0;
}