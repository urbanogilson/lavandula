#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void useCorsPolicy(AppBuilder *builder, CorsConfig corsPolicy) {
    builder->app.corsPolicy = corsPolicy;
}

void useDefaultCorsPolicy(AppBuilder *builder) {
    builder->app.corsPolicy = corsPolicy();

    allowOrigin(&builder->app.corsPolicy, "*");

    allowMethod(&builder->app.corsPolicy, HTTP_GET);
    allowMethod(&builder->app.corsPolicy, HTTP_POST);
    allowMethod(&builder->app.corsPolicy, HTTP_PUT);
    allowMethod(&builder->app.corsPolicy, HTTP_PATCH);
    allowMethod(&builder->app.corsPolicy, HTTP_DELETE);
    allowMethod(&builder->app.corsPolicy, HTTP_OPTIONS);
}

void useHttpsRedirect(AppBuilder *builder) {
    builder->app.useHttpsRedirect = true;
}

void useEnvironment(AppBuilder *builder, char *env) {
    builder->app.environment = env;
}

bool isDevelopment(AppBuilder *builder) {
    char *env = builder->app.environment;
    if (!env) return false;

    if (strcmp(env, "DEVELOPMENT") == 0) {
        return true;
    }

    return false;
}

bool isProduction(AppBuilder *builder) {
    char *env = builder->app.environment;
    if (!env) return false;

    if (strcmp(env, "PRODUCTION") == 0) {
        return true;
    }

    return false;
}

bool isTesting(AppBuilder *builder) {
    char *env = builder->app.environment;
    if (!env) return false;

    if (strcmp(env, "TESTING") == 0) {
        return true;
    }

    return false;
}

void useDotenv(char *path) {
    dotenv(path);
}

App build(AppBuilder builder)
{
    builder.app.server = initServer(builder.app.port);

    return builder.app;
}

void runApp(App *app) {
    runServer(&app->server, app->middleware);
}

void cleanupApp(App *app) {
    if (!app) return;
    
    freeServer(&app->server);
    dotenvClean();
    freeCorsConfiguration(&app->corsPolicy);
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

void options(App *app, char *path, Controller controller) {
    route(&app->server.router, HTTP_OPTIONS, path, controller);
}

// defines a route for 404 not found
void routeNotFound(App *app, Controller controller) {
    route(&app->server.router, HTTP_GET, "/404", controller);
}

// defines a route for GET /
void root(App *app, Controller controller) {
    route(&app->server.router, HTTP_GET, "/", controller);
}