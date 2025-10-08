#ifndef auth_h
#define auth_h

#include "http.h"
#include "router.h"
#include "middleware.h"

typedef struct {
    char **credentials;
    int    credentialsCount;
    int    credentialsCapacity;
} BasicAuthenticator;

BasicAuthenticator initBasicAuth();
HttpResponse basicAuth(AppContext context, MiddlewareHandler *n);
HttpResponse basicAuthWithCredentials(BasicAuthenticator *auth, AppContext context, MiddlewareHandler *n);
void freeBasicAuth(BasicAuthenticator);

void authenticateBasicCredentials(BasicAuthenticator *auth, char *base64);
void addBasicCredentials(BasicAuthenticator *auth, char *username, char *password);
bool checkBasicCredentials(BasicAuthenticator *auth, char *base64);

#endif