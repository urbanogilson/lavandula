#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "lavandula_test.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

HttpResponse notFound(HttpRequest _) {
    return response("Not Found", HTTP_NOT_FOUND);
}

bool authenticator(HttpRequest req, MiddlewareHandler *n) {
    printf("Authenticating: %s\n", req.resource);

    bool authed = true; // auth logic
    if (!authed) {
        return false;
    }

    return next(req, n);
}

void testOne() {
    int x = 10;
    expect(x, toBe(10));
}

void runTests() {
    runTest(testOne);
    runTest(testOne);
    runTest(testOne);
    runTest(testOne);

    testResults();
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        char *option = argv[1];
        if (strcmp(option, "new") == 0) {
            if (argc < 3) {
                printf("error: expected project name after 'new'\n");
                return 1;
            }

            char *projectName = argv[2];
            newProject(projectName);

            return 0;
        }
    }

    runTests();

    AppBuilder builder = createBuilder();
    usePort(&builder, 3005);

    useMiddleware(&builder, logger);
    useMiddleware(&builder, authenticator);

    // 1. PostgreSL, MySQL, SQLite integrations, etc
    //    - build an actual mini backend with it
    // 2. Look at Dependency Injection containers
    // 3. CORS, Rate Limiting, etc
    // 4. Testing framework
    // 5. More HTTP features (file serving, etc)

    App app = build(builder);

    root(&app.server.router, home);
    routeNotFound(&app.server.router, notFound);

    runApp(&app);

    cleanupApp(&app);

    return 0;
}