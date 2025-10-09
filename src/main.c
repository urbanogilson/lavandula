#include "include/lavandula.h"

appRoute(home) {
    return ok("Method Not Allowed");
}

int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);
    
    App app = build(builder);
    addBasicCredentials(&app.auth, "admin", "password");

    useGlobalMiddleware(&builder, basicAuth);

    Route homeRoute = root(&app, home);
    useLocalMiddleware(&homeRoute, basicAuth);

    runApp(&app);
}