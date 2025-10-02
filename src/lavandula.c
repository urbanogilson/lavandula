#include <stdio.h>
#include <stdlib.h>

#include "lavandula.h"

AppBuilder createBuilder() {
    AppBuilder builder = {
        .app.port = 3000,
        .app.verboseLogging = false,
    };

    builder.app.middleware = (MiddlewareHandler) {
        .handlers = malloc(sizeof(MiddlewareHandler) * 1),
        .count = 0,
        .capacity = 1,
    };

    return builder;
}

void usePort(AppBuilder *builder, int port) {
    builder->app.port = port;
}

void useMiddleware(AppBuilder *builder, MiddlewareFunc middleware) {
    if (builder->app.middleware.count >= builder->app.middleware.capacity) {
        builder->app.middleware.capacity *= 2;
        builder->app.middleware.handlers = realloc(builder->app.middleware.handlers, sizeof(MiddlewareFunc) * builder->app.middleware.capacity);
    }
    builder->app.middleware.handlers[builder->app.middleware.count++] = middleware;
}

void useVerboseLogging(AppBuilder *builder) {
    builder->app.verboseLogging = true;
}

App build(AppBuilder builder) {
    builder.app.server = initServer(builder.app.port);

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

void put(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_PUT, path, controller);
}

void delete(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_DELETE, path, controller);
}

void patch(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_PATCH, path, controller);
}

// defines a route for 404 not found
void routeNotFound(App *app, Controller controller) {
    route(&app->server.router, HTTP_GET, "/404", controller);
}

// defines a route for GET /
void root(App *app, Controller controller) {
    route(&app->server.router, HTTP_GET, "/", controller);
}