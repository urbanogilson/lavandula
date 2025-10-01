#include <stdio.h>

#include "lavandula_test.h"

void testFailed() {
    assertionsFailed++;
}

void runTest(TestFunction test) {
    test();
    
    testsRan++;
}

void testResults() {
    printf("\n\nTest Results:\n");
    printf("  tests ran:         %d\n", testsRan);
    printf("  tests failed:      %d\n", testsFailed);
    printf("  assertions:        %d\n", assertions);
    printf("  assertions failed: %d\n", assertionsFailed);

    printf("\n");
}