#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/utils.h"

void test_read_file_exists() {
    FILE *temp = fopen("test_utils.tmp", "w");
    fprintf(temp, "Hello, World!\nThis is a test file.\n");
    fclose(temp);
    
    char *content = readFile("test_utils.tmp");
    
    expect(content != NULL, toBe(1));
    expect(strcmp(content, "Hello, World!\nThis is a test file.\n"), toBe(0));
    
    free(content);
    remove("test_utils.tmp");
}

void test_read_file_nonexistent() {
    char *content = readFile("nonexistent_file.txt");
    
    expect(content == NULL, toBe(1));
}

void test_read_empty_file() {
    FILE *temp = fopen("empty_test.tmp", "w");
    fclose(temp);
    
    char *content = readFile("empty_test.tmp");
    
    expect(content != NULL, toBe(1));
    expect(strcmp(content, ""), toBe(0));
    
    free(content);
    remove("empty_test.tmp");
}

void test_read_file_with_newlines() {
    FILE *temp = fopen("newlines_test.tmp", "w");
    fprintf(temp, "Line 1\nLine 2\n\nLine 4\n");
    fclose(temp);
    
    char *content = readFile("newlines_test.tmp");
    
    expect(content != NULL, toBe(1));
    expect(strcmp(content, "Line 1\nLine 2\n\nLine 4\n"), toBe(0));
    
    free(content);
    remove("newlines_test.tmp");
}

void test_read_file_large_content() {
    FILE *temp = fopen("large_test.tmp", "w");
    for (int i = 0; i < 100; i++) {
        fprintf(temp, "This is line number %d with some additional content to make it longer.\n", i);
    }
    fclose(temp);
    
    char *content = readFile("large_test.tmp");
    
    expect(content != NULL, toBe(1));
    expect(strncmp(content, "This is line number 0", 21), toBe(0));
    expect(strstr(content, "This is line number 50") != NULL, toBe(1));
    expect(strstr(content, "This is line number 99") != NULL, toBe(1));
    
    free(content);
    remove("large_test.tmp");
}

void test_read_file_utf8_content() {
    FILE *temp = fopen("utf8_test.tmp", "w");
    fprintf(temp, "UTF-8 test: café, naïve, résumé, 你好, мир");
    fclose(temp);
    
    char *content = readFile("utf8_test.tmp");
    
    expect(content != NULL, toBe(1));
    expect(strcmp(content, "UTF-8 test: café, naïve, résumé, 你好, мир"), toBe(0));
    
    free(content);
    remove("utf8_test.tmp");
}

void run_utils_tests() {
    runTest(test_read_file_exists);
    runTest(test_read_file_nonexistent);
    runTest(test_read_empty_file);
    runTest(test_read_file_with_newlines);
    runTest(test_read_file_large_content);
    runTest(test_read_file_utf8_content);
}