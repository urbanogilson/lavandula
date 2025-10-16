#include "lavandula.h"

appRoute(home, ctx) {
    return ok("Hello, World!", TEXT_PLAIN);
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