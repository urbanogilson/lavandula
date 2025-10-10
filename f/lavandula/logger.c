#include <stdio.h>

#include "include/logger.h"

void logInfo(char *msg) {
    printf("[info]: %s", msg);
}

void logWarning(char *msg) {
    printf("[warning]: %s", msg);
}

void logError(char *msg) {
    printf("[error]: %s", msg);
}

HttpResponse logger(AppContext context, MiddlewareHandler *n) {
    printf("Logger: %s: '%s'\n", httpMethodToStr(context.request.method), context.request.resource);

    return next(context, n);
}

HttpResponse fileLogger(AppContext context, MiddlewareHandler *n) {
    if (!n) {
        return (HttpResponse) {
            .content = "Internal Server Error",
            .status = HTTP_INTERNAL_SERVER_ERROR
        };
    }
    if (!context.request.body) {
        return (HttpResponse) {
            .content = "Bad Request",
            .status = HTTP_BAD_REQUEST
        };
    }

    return (HttpResponse) {
        .content = "Bad Request",
        .status = HTTP_BAD_REQUEST
    };
}