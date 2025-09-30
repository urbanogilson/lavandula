#include "../src/lavandula.h"

HttpResponse logger(HttpRequest request, Controller controller) {
    printf("requesting: %s", request.resource);

    return controller(request);
}

HttpResponse index(HttpRequest request) {
    return ok("Hello, World!");
}

int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 3001);
    useMiddleware(&builder, logger);

    dotenv();

    char *dbUser = env("DB_USER");
    char *dbPass = env("DB_PASS");

    App app = build(builder);

    get(&app, "/get", index);

    runApp(&app);

    dotenvClean();
    cleanupApp(&app);

    return 0;
}