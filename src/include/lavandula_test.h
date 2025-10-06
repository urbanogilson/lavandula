#ifndef test_h
#define test_h

extern int testsRan;
extern int testsFailed;
extern int assertions;
extern int assertionsFailed;

typedef void (*TestFunction)();

void runTest(TestFunction);
void testResults();
void testFailed();

#define expect(x, n) do { \
    assertions++; \
    if ((x) != (n)) { \
        assertionsFailed++; \
        testFailed(); \
    } \
} while(0)

#define toBe(x) x

#endif