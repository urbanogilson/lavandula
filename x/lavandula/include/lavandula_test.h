#ifndef test_h
#define test_h

#include <stdio.h>

extern int testsRan;
extern int testsFailed;
extern int assertions;
extern int assertionsFailed;
extern const char* currentTestName;

typedef void (*TestFunction)();

void runTest(TestFunction);
void testResults();
void testFailed();

#define expect(x, n) do { \
    assertions++; \
    if ((x) != (n)) { \
        assertionsFailed++; \
        printf("FAILED: %s at line %d - expected %s to be %s\n", \
               currentTestName ? currentTestName : "Unknown Test", \
               __LINE__, #x, #n); \
        testFailed(); \
    } \
} while(0)

#define runTest(func) do { \
    currentTestName = #func; \
    func(); \
    testsRan++; \
} while(0)

#define toBe(x) x

#endif