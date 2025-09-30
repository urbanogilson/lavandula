#include <stdio.h>

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

HttpResponse logger(HttpRequest request, Controller controller) {
    printf("requesting: %s\n", request.resource);

    return controller(request);
}