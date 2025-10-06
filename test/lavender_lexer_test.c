#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/lavender_lexer.h"

void test_lexer_initialization() {
    LavenderLexer lexer = newLexer("test source");
    
    expect(lexer.position, toBe(0));
    expect(lexer.tokenCount, toBe(0));
    expect(lexer.tokenCapacity, toBe(1));
    expect(lexer.hadError, toBe(0));
    
    freeLexer(&lexer);
}

void test_tokenize_simple_model() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "model User {}");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(4));
    expect(lexer.hadError, toBe(0));
    
    expect(lexer.tokens[0].type, toBe(SCHEMA_TOKEN_MODEL));
    expect(lexer.tokens[1].type, toBe(SCHEMA_TOKEN_IDENTIFIER));
    expect(lexer.tokens[2].type, toBe(SCHEMA_TOKEN_LBRACE));
    expect(lexer.tokens[3].type, toBe(SCHEMA_TOKEN_RBRACE));
    
    expect(strcmp(lexer.tokens[0].lexeme, "model"), toBe(0));
    expect(strcmp(lexer.tokens[1].lexeme, "User"), toBe(0));
    expect(strcmp(lexer.tokens[2].lexeme, "{"), toBe(0));
    expect(strcmp(lexer.tokens[3].lexeme, "}"), toBe(0));
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_tokenize_with_whitespace() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "  model   Todo   {  }  ");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(4));
    expect(lexer.hadError, toBe(0));
    
    expect(lexer.tokens[0].type, toBe(SCHEMA_TOKEN_MODEL));
    expect(lexer.tokens[1].type, toBe(SCHEMA_TOKEN_IDENTIFIER));
    expect(lexer.tokens[2].type, toBe(SCHEMA_TOKEN_LBRACE));
    expect(lexer.tokens[3].type, toBe(SCHEMA_TOKEN_RBRACE));
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_tokenize_symbols() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "@ ( ) { }");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(5));
    expect(lexer.hadError, toBe(0));
    
    expect(lexer.tokens[0].type, toBe(SCHEMA_TOKEN_AT));
    expect(lexer.tokens[1].type, toBe(SCHEMA_TOKEN_LPAREN));
    expect(lexer.tokens[2].type, toBe(SCHEMA_TOKEN_RPAREN));
    expect(lexer.tokens[3].type, toBe(SCHEMA_TOKEN_LBRACE));
    expect(lexer.tokens[4].type, toBe(SCHEMA_TOKEN_RBRACE));
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_tokenize_numbers() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "123 456 789");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(3));
    expect(lexer.hadError, toBe(0));
    
    expect(lexer.tokens[0].type, toBe(SCHEMA_TOKEN_NUMBER));
    expect(lexer.tokens[1].type, toBe(SCHEMA_TOKEN_NUMBER));
    expect(lexer.tokens[2].type, toBe(SCHEMA_TOKEN_NUMBER));
    
    expect(strcmp(lexer.tokens[0].lexeme, "123"), toBe(0));
    expect(strcmp(lexer.tokens[1].lexeme, "456"), toBe(0));
    expect(strcmp(lexer.tokens[2].lexeme, "789"), toBe(0));
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_tokenize_identifiers() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fprintf(temp, "User Todo id name_field field123");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(5));
    expect(lexer.hadError, toBe(0));
    
    for (int i = 0; i < 5; i++) {
        expect(lexer.tokens[i].type, toBe(SCHEMA_TOKEN_IDENTIFIER));
    }
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void test_token_utility_functions() {
    SchemaToken token = newToken("test", SCHEMA_TOKEN_IDENTIFIER);
    
    expect(token.type, toBe(SCHEMA_TOKEN_IDENTIFIER));
    expect(strcmp(token.lexeme, "test"), toBe(0));
    
    freeToken(&token);
    
    expect(token.lexeme == NULL, toBe(1));
}

void test_empty_file() {
    FILE *temp = fopen("test_schema.tmp", "w");
    fclose(temp);
    
    LavenderLexer lexer = newLexer("test_schema.tmp");
    tokenizeSchema(&lexer);
    
    expect(lexer.tokenCount, toBe(0));
    expect(lexer.hadError, toBe(0));
    
    freeLexer(&lexer);
    remove("test_schema.tmp");
}

void run_lexer_tests() {
    runTest(test_lexer_initialization);
    runTest(test_tokenize_simple_model);
    runTest(test_tokenize_with_whitespace);
    runTest(test_tokenize_symbols);
    runTest(test_tokenize_numbers);
    runTest(test_tokenize_identifiers);
    runTest(test_token_utility_functions);
    runTest(test_empty_file);
}