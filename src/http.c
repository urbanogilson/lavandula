#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"

static inline char currentChar(HttpParser *parser) {
    return parser->requestBuffer[parser->position];
}

static inline void advance(HttpParser *parser) {
    parser->position++;
}

static inline bool isEnd(HttpParser parser) {
    return parser.position >= parser.requestLength;
}

static HttpMethod toHttpMethod(char *s) {
    if (strcmp(s, "GET") == 0) {
        return HTTP_GET;
    }
    if (strcmp(s, "POST") == 0) {
        return HTTP_POST;
    }
    if (strcmp(s, "PUT") == 0) {
        return HTTP_PUT;
    }
    if (strcmp(s, "PATCH") == 0) {
        return HTTP_PATCH;
    }
    if (strcmp(s, "DELETE") == 0) {
        return HTTP_DELETE;
    }

    return HTTP_GET;
}

static char* httpMethodToStr(HttpMethod method) {
    switch (method) {
        case HTTP_GET: {
            return "GET";
        }
        case HTTP_POST: {
            return "POST";
        }
        case HTTP_PUT: {
            return "PUT";
        }
        case HTTP_PATCH: {
            return "PATCH";
        }
        case HTTP_DELETE: {
            return "DELETE";
        }
        default: {
            return "UNKNOWN";
        }
    }
}

static void skipWhitespace(HttpParser *parser) {
    while (!isEnd(*parser) && (currentChar(parser) == ' ' || currentChar(parser) == '\r' || currentChar(parser) == '\n')) {
        advance(parser);
    }
}

static char *parseTokenUntil(HttpParser *parser, char delimiter) {
    int capacity = 32;
    int length = 0;
    char *token = malloc(capacity);

    while (!isEnd(*parser) && currentChar(parser) != delimiter && currentChar(parser) != '\r' && currentChar(parser) != '\n') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            token = realloc(token, capacity);
        }
        token[length++] = currentChar(parser);
        advance(parser);
    }
    token[length] = '\0';
    return token;
}

static void parseHeaders(HttpParser *parser) {
    parser->request.headerCapacity = 8;
    parser->request.headerCount = 0;
    parser->request.headers = malloc(sizeof(Header) * parser->request.headerCapacity);

    while (!isEnd(*parser)) {
        if (currentChar(parser) == '\r' && parser->position + 1 < parser->requestLength && parser->requestBuffer[parser->position + 1] == '\n') {
            advance(parser);
            advance(parser);
            break;
        }

        char *name = parseTokenUntil(parser, ':');
        if (!isEnd(*parser) && currentChar(parser) == ':') advance(parser);
        skipWhitespace(parser);
        char *value = parseTokenUntil(parser, '\r');

        if (!isEnd(*parser) && currentChar(parser) == '\r') advance(parser);
        if (!isEnd(*parser) && currentChar(parser) == '\n') advance(parser);

        if (parser->request.headerCount >= parser->request.headerCapacity) {
            parser->request.headerCapacity *= 2;
            parser->request.headers = realloc(parser->request.headers, sizeof(Header) * parser->request.headerCapacity);
        }

        int headerCount = parser->request.headerCount;

        strncpy(parser->request.headers[headerCount].name, name, MAX_HEADER_NAME - 1);
        parser->request.headers[headerCount].name[MAX_HEADER_NAME - 1] = '\0';
        strncpy(parser->request.headers[headerCount].value, value, MAX_HEADER_VALUE - 1);
        parser->request.headers[headerCount].value[MAX_HEADER_VALUE - 1] = '\0';

        parser->request.headerCount++;

        free(name);
        free(value);
    }
}


void printHeaders(HttpParser *parser) {
    printf("\nRequest:\n");
    printf("  Method: %s\n", httpMethodToStr(parser->request.method));
    printf("  Resource: %s\n", parser->request.resource);

    printf("Headers (%d):\n", parser->request.headerCount);
    for (int i = 0; i < parser->request.headerCount; i++) {
        printf("  HEADER '%s':  %s\n", parser->request.headers[i].name, parser->request.headers[i].value);
    }
}

HttpParser parseRequest(char *request) {
    HttpParser parser = {
        .isValid = true,
        .requestBuffer = strdup(request),
        .requestLength = strlen(request),
        .position = 0,
    };

    char method[16];
    int methodIndex = 0;
    while (!isEnd(parser) && currentChar(&parser) != ' ' && methodIndex < sizeof(method) - 1) {
        method[methodIndex++] = currentChar(&parser);
        advance(&parser);
    }
    method[methodIndex] = '\0';

    if (!isEnd(parser)) advance(&parser);

    char *url = parseTokenUntil(&parser, ' ');
    if (!isEnd(parser)) advance(&parser);

    parser.request.method = toHttpMethod(method);
    parser.request.resource = url;

    char *version = parseTokenUntil(&parser, '\r');
    strncpy(parser.request.version, version, sizeof(parser.request.version) - 1);
    parser.request.version[sizeof(parser.request.version) - 1] = '\0';
    free(version);

    if (!isEnd(parser) && currentChar(&parser) == '\r') advance(&parser);
    if (!isEnd(parser) && currentChar(&parser) == '\n') advance(&parser);

    parseHeaders(&parser);
    // printHeaders(&parser);

    return parser;
}


void freeParser(HttpParser *parser) {
    if (!parser) return;

    free(parser->requestBuffer);
    free(parser->request.resource);

    for (int i = 0; i < parser->request.headerCount; i++) {

    }
    free(parser->request.headers);

    free(parser->request.body);
}