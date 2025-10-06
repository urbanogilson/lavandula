#include "include/middleware.h"

bool next(AppContext context, MiddlewareHandler *middleware) {
    if (middleware->current < middleware->count) {
        MiddlewareFunc handler = middleware->handlers[middleware->current++];
        if (handler) {
            return handler(context, middleware);
        }

        return false;
    }
    else {
        if (middleware->finalHandler) {
            middleware->finalHandler(context);
        }

        return true;
    }
}