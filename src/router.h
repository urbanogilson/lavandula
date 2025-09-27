#ifndef router_h
#define router_h

#include "http.h"

typedef HttpResponse (*Controller)();

HttpResponse ok(char *content);
HttpResponse badRequest(char *content);

typedef struct {
    HttpMethod method;
    char      *path;
    Controller controller;
} Route;

typedef struct {
    Route *routes;
    int    routeCount;
    int    routeCapacity;
} Router;

Router initRouter();
void   freeRouter(Router *router);

void   route(Router *router, HttpMethod method, char *path, Controller controller);

#endif