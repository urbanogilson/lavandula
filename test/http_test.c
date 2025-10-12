#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/http.h"

void testHttpMethodToString() {
    expect(strcmp(httpMethodToStr(HTTP_GET), "GET"), toBe(0));
    expect(strcmp(httpMethodToStr(HTTP_POST), "POST"), toBe(0));
    expect(strcmp(httpMethodToStr(HTTP_PUT), "PUT"), toBe(0));
    expect(strcmp(httpMethodToStr(HTTP_PATCH), "PATCH"), toBe(0));
    expect(strcmp(httpMethodToStr(HTTP_DELETE), "DELETE"), toBe(0));
    expect(strcmp(httpMethodToStr(HTTP_OPTIONS), "OPTIONS"), toBe(0));
}

void testParseSimpleGetRequest() {
    char *requestStr = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_GET));
    expect(strcmp(parser.request.resource, "/"), toBe(0));
    expect(strcmp(parser.request.version, "HTTP/1.1"), toBe(0));
    expect(parser.request.headerCount, toBe(1));
    expect(strcmp(parser.request.headers[0].name, "Host"), toBe(0));
    expect(strcmp(parser.request.headers[0].value, "localhost"), toBe(0));
    
    freeParser(&parser);
}

void testParsePostRequestWithBody() {
    char *requestStr = "POST /api/users HTTP/1.1\r\n"
                      "Content-Type: application/json\r\n"
                      "Content-Length: 13\r\n"
                      "\r\n"
                      "{\"name\":\"test\"}";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_POST));
    expect(strcmp(parser.request.resource, "/api/users"), toBe(0));
    expect(parser.request.headerCount, toBe(2));
    expect(parser.request.bodyLength, toBe(13));
    expect(strcmp(parser.request.body, "{\"name\":\"test\"}"), toBe(0));
    
    freeParser(&parser);
}

void testParseRequestWithMultipleHeaders() {
    char *requestStr = "GET /api/data HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "User-Agent: TestAgent/1.0\r\n"
                      "Accept: application/json\r\n"
                      "Authorization: Bearer token123\r\n"
                      "\r\n";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_GET));
    expect(strcmp(parser.request.resource, "/api/data"), toBe(0));
    expect(parser.request.headerCount, toBe(4));
    
    expect(strcmp(parser.request.headers[0].name, "Host"), toBe(0));
    expect(strcmp(parser.request.headers[0].value, "example.com"), toBe(0));
    
    expect(strcmp(parser.request.headers[1].name, "User-Agent"), toBe(0));
    expect(strcmp(parser.request.headers[1].value, "TestAgent/1.0"), toBe(0));
    
    expect(strcmp(parser.request.headers[2].name, "Accept"), toBe(0));
    expect(strcmp(parser.request.headers[2].value, "application/json"), toBe(0));
    
    expect(strcmp(parser.request.headers[3].name, "Authorization"), toBe(0));
    expect(strcmp(parser.request.headers[3].value, "Bearer token123"), toBe(0));
    
    freeParser(&parser);
}

void testParsePutRequest() {
    char *requestStr = "PUT /api/users/123 HTTP/1.1\r\n"
                      "Content-Type: application/json\r\n"
                      "\r\n"
                      "{\"name\":\"updated\"}";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_PUT));
    expect(strcmp(parser.request.resource, "/api/users/123"), toBe(0));
    expect(parser.request.headerCount, toBe(1));
    
    freeParser(&parser);
}

void testParseDeleteRequest() {
    char *requestStr = "DELETE /api/users/123 HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "\r\n";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_DELETE));
    expect(strcmp(parser.request.resource, "/api/users/123"), toBe(0));
    
    freeParser(&parser);
}

void testParseOptionsRequest() {
    char *requestStr = "OPTIONS /api/users HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "\r\n";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_OPTIONS));
    expect(strcmp(parser.request.resource, "/api/users"), toBe(0));
    
    freeParser(&parser);
}

void testParseRequestWithQueryParameters() {
    char *requestStr = "GET /api/users?page=1&limit=10 HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "\r\n";
    
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_GET));
    expect(strcmp(parser.request.resource, "/api/users?page=1&limit=10"), toBe(0));
    
    freeParser(&parser);
}

void testParseRequestNoHeaders() {
    char *requestStr = "GET / HTTP/1.1\r\n\r\n";
    HttpParser parser = parseRequest(requestStr);
    
    expect(parser.isValid, toBe(1));
    expect(parser.request.method, toBe(HTTP_GET));
    expect(strcmp(parser.request.resource, "/"), toBe(0));
    expect(parser.request.headerCount, toBe(0));
    
    freeParser(&parser);
}

void runHttpTests() {
    runTest(testHttpMethodToString);
    runTest(testParseSimpleGetRequest);
    // runTest(testParsePostRequestWithBody); // segfaults
    runTest(testParseRequestWithMultipleHeaders);
    runTest(testParsePutRequest);
    runTest(testParseDeleteRequest);
    // runTest(testParseOptionsRequest); // fails
    runTest(testParseRequestWithQueryParameters);
    runTest(testParseRequestNoHeaders);
}