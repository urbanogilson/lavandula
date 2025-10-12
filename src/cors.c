#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/cors.h"

#define ORIGIN_LIMIT 50
#define HEADER_LIMIT 50

CorsConfig corsPolicy() {
    CorsConfig config = {
        .allowOrigin = malloc(ORIGIN_LIMIT * sizeof(char*)),
        .allowOriginCount = 0,
        .allowMethods = {0},
        .methodCount = 0,
        .allowHeaders = malloc(HEADER_LIMIT * sizeof(char*)),
        .headerCount = 0,
    };

    if (!config.allowOrigin || !config.allowHeaders) {
        fprintf(stderr, "Fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return config;
}

void allowOrigin(CorsConfig *config, char *origin) {
    if (config->allowOriginCount >= ORIGIN_LIMIT) {
        return;
    }

    config->allowOrigin[config->allowOriginCount++] = origin;
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

void allowHeader(CorsConfig *config, char *header) {
    if (config->headerCount >= HEADER_LIMIT) {
        return;
    }

    config->allowHeaders[config->headerCount++] = header;
}

void allowAnyHeader(CorsConfig *config) {
    allowHeader(config, "*");
}

CorsConfig corsAllowAll() {
    CorsConfig config = corsPolicy();
    allowAnyOrigin(&config);
    allowAnyMethod(&config);

    return config;
}