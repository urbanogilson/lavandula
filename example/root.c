#include "../src/lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    // Special path for the root URL
    root(&app, home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}