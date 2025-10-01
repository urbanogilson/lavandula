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

bool logger(HttpRequest request, MiddlewareHandler *n) {
    printf("%s: '%s'\n", httpMethodToStr(request.method), request.resource);

    return next(request, n);
}

bool fileLogger(HttpRequest request, MiddlewareHandler *n) {
    if (!n) return false;
    if (!request.body) return false;

    return false;
}