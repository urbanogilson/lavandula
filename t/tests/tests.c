#include "../src/lavandula.h"

void aTest() {
   int x = 10;
   expect(x, toBe(10));
}

void runTests() {
   runTest(aTest);
   // ..
}

// call 'runTests' in main.c