#include <stddef.h>
#include <stdlib.h>
#include "include/middleware.h"

HttpResponse next(AppContext context, MiddlewareHandler *middleware) {
    while (middleware->current < middleware->count) {
        MiddlewareFunc handler = middleware->handlers[middleware->current++];
        if (handler) {
            HttpResponse response = handler(context, middleware);

            if (response.content != NULL) {
                return response;
            }
        }
    }
    
    if (middleware->finalHandler) {
        return middleware->finalHandler(context);
    }
    
    HttpResponse notFoundResponse = {
        .content = "Not Found",
        .status = HTTP_NOT_FOUND
    };

    return notFoundResponse;
}