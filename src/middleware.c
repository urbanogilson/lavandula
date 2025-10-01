#include "middleware.h"

bool next(HttpRequest request, MiddlewareHandler *middleware) {
    if (middleware->current < middleware->count) {
        MiddlewareFunc handler = middleware->handlers[middleware->current++];
        if (handler) {
            return handler(request, middleware);
        }

        return false;
    }
    else {
        if (middleware->finalHandler) {
            middleware->finalHandler(request);
        }

        return true;
    }
}