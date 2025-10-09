#include "include/lavandula.h"

HttpResponse globalMiddleware(AppContext ctx, MiddlewareHandler *middleware) {
    printf("Global middleware: Before request processing\n");
    
    return next(ctx, middleware);
}

appRoute(home) {
    return ok("Hello, World");
}

int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 3001);
    useMiddleware(&builder, globalMiddleware);
    
    App app = build(builder);

    Route homeRoute = root(&app, home);
    useRouteMiddleware(&homeRoute, logger);

    runApp(&app);
}