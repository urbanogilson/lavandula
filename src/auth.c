#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/auth.h"
#include "include/base64.h"
#include "include/router.h"

BasicAuthenticator initBasicAuth() {
    BasicAuthenticator auth = {
        .credentials = malloc(sizeof(char *)),
        .credentialsCount = 0,
        .credentialsCapacity = 1
    };

    return auth;
}

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

void authenticateBasicCredentials(BasicAuthenticator *auth, char *base64) {
    if (auth->credentialsCount >= auth->credentialsCapacity) {
        auth->credentialsCapacity *= 2;
        auth->credentials = realloc(auth->credentials, sizeof(char *) * auth->credentialsCapacity);
    }

    auth->credentials[auth->credentialsCount++] = strdup(base64);
}

void addBasicCredentials(BasicAuthenticator *auth, char *username, char *password) {
    int credLen = strlen(username) + strlen(password) + 2;
    char *credentials = malloc(credLen);
    snprintf(credentials, credLen, "%s:%s", username, password);
    
    char *encoded = base64Encode(credentials);
    free(credentials);
    
    authenticateBasicCredentials(auth, encoded);
    free(encoded);
}

HttpResponse basicAuthWithCredentials(BasicAuthenticator *auth, AppContext context, MiddlewareHandler *n) {
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
    
    if (checkBasicCredentials(auth, encodedCredentials)) {
        return next(context, n);
    } else {
        return unauthorized("Unauthorized");
    }
}

bool checkBasicCredentials(BasicAuthenticator *auth, char *base64) {
    for (int i = 0; i < auth->credentialsCount; i++) {
        if (strcmp(auth->credentials[i], base64) == 0) {
            return true;
        }
    }

    return false;
}

void freeBasicAuth(BasicAuthenticator auth) {
    if (!auth.credentials) {
        return;
    }

    for (int i = 0; i < auth.credentialsCount; i++) {
        free(auth.credentials[i]);
    }

    free(auth.credentials);
}