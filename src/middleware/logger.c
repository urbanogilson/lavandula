#include <stdio.h>

#include "../include/logger.h"

void logInfo(char *msg) {
    printf("[info]: %s\n", msg);
}

void logWarning(char *msg) {
    printf("[warning]: %s\n", msg);
}

void logError(char *msg) {
    printf("[error]: %s\n", msg);
}

middleware(consoleLogger, ctx, m) {
    printf("Logger: %s: '%s'\n", httpMethodToStr(ctx.request.method), ctx.request.resource);

    return next(ctx, m);
}