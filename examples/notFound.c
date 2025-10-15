#include "lavandula.h"

appRoute(notFound) {
    return response("Route not found", HTTP_NOT_FOUND, TEXT_PLAIN);
}

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    // Special path for the root URL
    routeNotFound(&app, notFound);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}