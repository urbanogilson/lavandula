#ifndef lavandula_h
#define lavandula_h

#include "cli.h"
#include "server.h"
#include "dotenv.h"
#include "middleware.h"
#include "logger.h"
#include "lavandula_test.h"

typedef struct {
    Server              server;
    int                 port;

    MiddlewareHandler  middleware;
} App;

typedef struct {
    App app;
} AppBuilder;

AppBuilder createBuilder();
void usePort(AppBuilder *builder, int port);
void useMiddleware(AppBuilder *builder, MiddlewareFunc);

App build(AppBuilder builder);

void runApp(App *app);
void cleanupApp(App *app);

void get(App *app, char *path, Controller controller);
void post(App *app, char *path, Controller controller);
void put(App *app, char *path, Controller controller);
void delete(App *app, char *path, Controller controller);
void patch(App *app, char *path, Controller controller);

// defines a special route for handling 404s
void   routeNotFound(Router *router,  Controller controller);

// defines a special route for handling the root path
void   root(Router *router, Controller controller);


#endif