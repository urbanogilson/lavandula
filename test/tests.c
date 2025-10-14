#include <stdio.h>
#include <stdlib.h>
#include "../src/include/lavandula_test.h"

void runLexerTests();
// void run_parser_tests();
void runHttpTests();
void runUtilsTests();
void runAuthTests();
void runJsonTests();

int main() {
    testsRan = 0;
    testsFailed = 0;
    assertions = 0;
    assertionsFailed = 0;
    
    runLexerTests();
    // run_parser_tests();
    runHttpTests();
    runUtilsTests();
    runAuthTests();
    runJsonTests();

    printf("=== Lavandula Test Results ===\n");
    testResults();
    
    if (testsFailed > 0 || assertionsFailed > 0) {
        printf("❌ Some tests failed!\n");
        return 1;
    } else {
        printf("✅ All tests passed!\n");
        return 0;
    }
}