#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/cors.h"

CorsConfig corsPolicy() {
    return (CorsConfig){};
}

void allowOrigin(CorsConfig *config, char *origin) {
    config->allowOrigin = origin;
}

void allowMethod(CorsConfig *config, HttpMethod method) {
    if (config->methodCount < 6) {
        config->allowMethods[config->methodCount++] = method;
    }
}

void allowAnyOrigin(CorsConfig *config) {
    allowOrigin(config, "*");
}

void allowAnyMethod(CorsConfig *config) {
    for (int i = 0; i < 6; i++) {
        allowMethod(config, i);
    }
}

CorsConfig corsAllowAll() {
    CorsConfig config = corsPolicy();
    allowAnyOrigin(&config);
    allowAnyMethod(&config);

    return config;
}