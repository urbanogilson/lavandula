#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/auth.h"
#include "include/base64.h"
#include "include/router.h"

HttpResponse basicAuth(AppContext context, MiddlewareHandler *n) {
    char *authHeader = NULL;
    for (int i = 0; i < context.request.headerCount; i++) {
        if (strcmp(context.request.headers[i].name, "Authorization") == 0) {
            authHeader = context.request.headers[i].value;
            break;
        }
    }

    if (!authHeader || strncmp(authHeader, "Basic ", 6) != 0) {
        return unauthorized("Unauthorized");
    }

    char *encodedCredentials = authHeader + 6;
    char *decodedCredentials = base64Decode(encodedCredentials);
    if (!decodedCredentials) {
        return unauthorized("Unauthorized");
    }

    char *colonPos = strchr(decodedCredentials, ':');
    if (!colonPos) {
        free(decodedCredentials);
        return unauthorized("Unauthorized");
    }

    *colonPos = '\0';
    char *username = decodedCredentials;
    char *password = colonPos + 1;

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        free(decodedCredentials);
        return next(context, n);
    } else {
        free(decodedCredentials);
        return unauthorized("Unauthorized");
    }
}