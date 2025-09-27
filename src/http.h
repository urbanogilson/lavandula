#ifndef http_h
#define http_h

#include <stdbool.h>

#define MAX_HEADER_NAME 64
#define MAX_HEADER_VALUE 256

typedef enum {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_PATCH,
    HTTP_DELETE
} HttpMethod;

typedef enum {
    HTTP_OK,          // 200
    HTTP_NOT_FOUND,   // 404
    HTTP_BAD_REQUEST, // 401
} HttpStatus;

typedef struct {
    char name[MAX_HEADER_NAME];
    char value[MAX_HEADER_VALUE];
} Header;

typedef struct {
    HttpMethod method;
    char      *resource;
    char       version[16];

    Header    *headers;
    int        headerCount;
    int        headerCapacity;

    char      *body;
    int        bodyLength;
} HttpRequest;

typedef struct {
    char      *content;
    HttpStatus status;
} HttpResponse;

typedef struct {
    HttpRequest request;
    bool        isValid;

    int         position;
    char       *requestBuffer;
    int         requestLength;
} HttpParser;

HttpParser parseRequest(char *request);
void       freeParser(HttpParser *parser);

#endif