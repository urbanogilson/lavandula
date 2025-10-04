#include <stdio.h>

#include "logger.h"
#include "logger.h"

void logInfo(char *msg) {
    printf("[info]: %s", msg);
}

void logWarning(char *msg) {
    printf("[warning]: %s", msg);
}

void logError(char *msg) {
    printf("[error]: %s", msg);
}

bool logger(AppContext context, MiddlewareHandler *n) {
    printf("%s: '%s'\n", httpMethodToStr(context.request.method), context.request.resource);

    return next(context, n);
}

bool fileLogger(AppContext context, MiddlewareHandler *n) {
    if (!n) return false;
    if (!context.request.body) return false;

    return false;
}