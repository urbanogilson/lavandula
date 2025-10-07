#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/lavender_parser.h"
#include "../src/include/lavender_lexer.h"
#include "../src/include/lavender_ast.h"

void test_parser_initialization() {
    LavenderLexer lexer = newLexer("test");
    LavenderParser parser = newParser(&lexer);
    
    expect(parser.lexer == &lexer, toBe(1));
    expect(parser.position, toBe(0));
    expect(parser.nodeCount, toBe(0));
    expect(parser.nodeCapacity, toBe(1));
    expect(parser.hadError, toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
}

void test_parse_simple_model() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User {}");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(0));
    expect(parser.nodeCount, toBe(1));
    expect(parser.nodes[0].type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(parser.nodes[0].model.name, "User"), toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_parse_multiple_models() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User {} model Todo {} model Post {}");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(0));
    expect(parser.nodeCount, toBe(3));
    
    expect(parser.nodes[0].type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(parser.nodes[0].model.name, "User"), toBe(0));
    
    expect(parser.nodes[1].type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(parser.nodes[1].model.name, "Todo"), toBe(0));
    
    expect(parser.nodes[2].type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(parser.nodes[2].model.name, "Post"), toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_expectToken_function() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    LavenderParser parser = newParser(&lexer);
    
    expect(expectToken(&parser, SCHEMA_TOKEN_MODEL), toBe(1));
    expect(parser.position, toBe(1));
    
    expect(expectToken(&parser, SCHEMA_TOKEN_IDENTIFIER), toBe(1));
    expect(parser.position, toBe(2));
    
    expect(expectToken(&parser, SCHEMA_TOKEN_LBRACE), toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_parse_with_whitespace() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "\n  model   User   {  \n  }  \n");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(0));
    expect(parser.nodeCount, toBe(1));
    expect(parser.nodes[0].type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(parser.nodes[0].model.name, "User"), toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_ast_utility_functions() {
    SchemaNode node;
    node.type = SCHEMA_NODE_MODEL;
    node.model.name = strdup("TestModel");
    
    expect(node.type, toBe(SCHEMA_NODE_MODEL));
    expect(strcmp(node.model.name, "TestModel"), toBe(0));
    
    freeSchemaNode(&node);
}

void test_empty_schema() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(0));
    expect(parser.nodeCount, toBe(0));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_invalid_model_syntax() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model {}");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(1));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_missing_opening_brace() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User }");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(1));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_missing_closing_brace() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User {");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    LavenderParser parser = newParser(&lexer);
    
    parseSchemaInternal(&parser);
    
    expect(parser.hadError, toBe(1));
    
    freeLavenderParser(&parser);
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void run_parser_tests() {
    runTest(test_parser_initialization);
    runTest(test_parse_simple_model);
    runTest(test_parse_multiple_models);
    runTest(test_expectToken_function);
    runTest(test_parse_with_whitespace);
    runTest(test_ast_utility_functions);
    runTest(test_empty_schema);
    runTest(test_invalid_model_syntax);
    runTest(test_missing_opening_brace);
    runTest(test_missing_closing_brace);
}