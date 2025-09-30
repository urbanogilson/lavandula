#ifndef lavandula_h
#define lavandula_h

#include "server.h"

typedef HttpResponse (*Middleware)(HttpRequest, Controller);

typedef struct {
    Server server;
    Middleware m;
    int port;
} App;

typedef struct {
    App app;
} AppBuilder;


AppBuilder createBuilder();
void usePort(AppBuilder *builder, int port);
void useMiddleware(AppBuilder *builder, Middleware);

App build(AppBuilder builder);

void runApp(App *app);
void cleanupApp(App *app);

#endif