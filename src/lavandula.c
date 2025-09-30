#include <stdio.h>

#include "lavandula.h"

AppBuilder createBuilder() {
    AppBuilder builder = {};
    usePort(&builder, 3000);

    return builder;
}

void usePort(AppBuilder *builder, int port) {
    builder->app.port = port;
}

void useMiddleware(AppBuilder *builder, Middleware middleware) {
    if (!builder->app.middleware.this) {
        builder->app.middleware.this = &middleware; // solution probably here
        builder->app.middleware.next = NULL;
    } else {
        builder->app.middleware.next = &(MiddlewarePipeline){
            .this = &middleware,
            .next = NULL,
        };
    }
}

App build(AppBuilder builder) {
    builder.app = (App){
        .server = initServer(builder.app.port)
    };

    return builder.app;
}

void runApp(App *app) {
    runServer(&app->server, app->middleware);
}

void cleanupApp(App *app) {
    if (!app) return;
    
    freeServer(&app->server);
}

void get(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_GET, path, controller);
}

void post(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_POST, path, controller);
}