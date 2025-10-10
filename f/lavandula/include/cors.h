#ifndef cors_h
#define cors_h

#include "http.h"

typedef struct {
    char     **allowOrigin;
    int        allowOriginCount;

    HttpMethod allowMethods[6];
    int        methodCount;

    char     **allowHeaders;     
    int        headerCount;
} CorsConfig;

CorsConfig corsPolicy();

void allowOrigin(CorsConfig *config, char *origin);
void allowMethod(CorsConfig *config, HttpMethod method);

void allowAnyOrigin(CorsConfig *config);
void allowAnyMethod(CorsConfig *config);

void allowHeader(CorsConfig *config, char *header);
void allowAnyHeader(CorsConfig *config);

CorsConfig corsAllowAll();

#endif