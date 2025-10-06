#ifndef cors_h
#define cors_h

#include "http.h"

typedef struct {
    char      *allowOrigin;

    HttpMethod allowMethods[6];
    int        methodCount;
} CorsConfig;

CorsConfig corsPolicy();

void allowOrigin(CorsConfig *config, char *origin);
void allowMethod(CorsConfig *config, HttpMethod method);
void allowAnyOrigin(CorsConfig *config);
void allowAnyMethod(CorsConfig *config);

CorsConfig corsAllowAll();

#endif