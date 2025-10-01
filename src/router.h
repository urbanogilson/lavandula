#ifndef router_h
#define router_h

#include "http.h"

typedef HttpResponse (*Controller)(HttpRequest);

HttpResponse ok(char *content);
HttpResponse badRequest(char *content);
HttpResponse response(char *content, HttpStatusCode);

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

// defines a special route for handling 404s
void   routeNotFound(Router *router,  Controller controller);

// defines a special route for handling the root path
void   root(Router *router, Controller controller);

#endif