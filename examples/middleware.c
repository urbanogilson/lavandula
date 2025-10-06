#include "lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    // Logging middleware example
    useMiddleware(&builder, logger);

    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}