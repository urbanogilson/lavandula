#ifndef middleware_h
#define middleware_h

#include "http.h"
#include "router.h"

typedef struct MiddlewareHandler MiddlewareHandler;

// A middleware function takes in a HttpRequest and a pointer to the next middleware handler.
typedef bool (* MiddlewareFunc)(AppContext, MiddlewareHandler *);

struct MiddlewareHandler {
    MiddlewareFunc *handlers;
    int count;
    int capacity;
    int current;
    Controller finalHandler;
};

bool next(AppContext context, MiddlewareHandler *middleware);

#endif