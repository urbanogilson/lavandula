#include "../src/lavandula.h"

void testOne() {
    int x = 10;
    expect(x, toBe(10));
}

int main() {
    runTest(testOne);
    testResults();

    AppBuilder builder = createBuilder();
    App app = build(builder);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}