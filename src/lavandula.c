#include "lavandula.h"

AppBuilder createBuilder() {
    AppBuilder builder = {};

    return builder;
}

void usePort(AppBuilder *builder, int port) {
    builder->app.port = port;
}

void useMiddleware(AppBuilder *builder, Middleware middleware) {
    builder->app.m = middleware;
}

App build(AppBuilder builder) {
    builder.app = (App){
        .server = initServer(builder.app.port)
    };

    return builder.app;
}

void runApp(App *app) {
    runServer(&app->server);
}

void cleanupApp(App *app) {
    if (!app) return;
    
    freeServer(&app->server);
}