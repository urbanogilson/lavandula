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
HttpResponse basicAuth(RequestContext context, MiddlewareHandler *);
void freeBasicAuth(BasicAuthenticator);

void addBasicCredentials(BasicAuthenticator *, char *username, char *password);
bool checkBasicCredentials(BasicAuthenticator *, char *base64);

#endif