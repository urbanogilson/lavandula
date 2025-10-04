#include "../../src/lavandula.h"
#include "routes.c"

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    registerRoutes(app);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}
