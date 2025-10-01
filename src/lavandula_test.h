#ifndef test_h
#define test_h

static int testsRan = 0;
static int testsFailed = 0;
static int assertions = 0;
static int assertionsFailed = 0;

typedef void (*TestFunction)();

void runTest(TestFunction);
void testResults();
void testFailed();

#define expect(x, n) if (x != n) { testFailed(); }
#define toBe(x) x

#endif