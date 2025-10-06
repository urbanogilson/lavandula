#include "lavandula.h"

HttpResponse notFound(HttpRequest _) {
    return response("Route not found", HTTP_NOT_FOUND);
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