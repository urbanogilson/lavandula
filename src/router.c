#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "router.h"
#include "server.h"

HttpResponse ok(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_OK
    };
}

HttpResponse badRequest(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_BAD_REQUEST
    };
}

HttpResponse response(char *content, HttpStatus status) {
    return (HttpResponse) {
        .content = content,
        .status = status
    };
}

Router initRouter() {
    Router router = {
        .routeCapacity = 1,
        .routeCount = 0,
        .routes = malloc(sizeof(Route))
    };

    return router;
}

void freeUIElement(UIElement *element) {
    switch (element->type) {
        case ELEMENT_TEXT: {
            Text *t = (Text *)element->data;
            free(t->text);
            break;
        }
        case ELEMENT_BOX: {
            break;
        }
        case ELEMENT_LINK_TO: {
            break;
        }
        default: {
            printf("unknown element in freeUIElement");
        }
    }
}

void freeRouter(Router *router) {
    if (!router) return;

    for (int i = 0; i < router->routeCount; i++) {
        Route route = router->routes[i];
        free(route.path);

        Page p = route.controller();
        free(p.title);


        for (int j = 0; j < p.bodyCount; j++) {
            UIElement element = p.body[j];
            freeUIElement(&element);
        }

        free(p.body);
    }

    free(router->routes);
}

void route(Router *router, HttpMethod method, char *path, Controller controller) {
    Route route = {
        .method = method,
        .path = strdup(path),
        .controller = controller
    };

    if (router->routeCount >= router->routeCapacity) {
        router->routeCapacity *= 2;
        router->routes = realloc(router->routes, sizeof(Route) * router->routeCapacity);
    }
    router->routes[router->routeCount++] = route;
}

void routeNotFound(Router *router, Controller controller) {
    route(router, HTTP_GET, "", controller);
}