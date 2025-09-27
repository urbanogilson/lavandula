#ifndef router_h
#define router_h

#include "http.h"
#include "ui.h"

typedef Page (*Controller)();

HttpResponse ok(char *content);
HttpResponse badRequest(char *content);
HttpResponse response(char *content, HttpStatus);

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
void   routeNotFound(Router *router,  Controller controller);

#endif