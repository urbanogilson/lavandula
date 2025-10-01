#ifndef logger_h
#define logger_h

#include "http.h"
#include "router.h"
#include "middleware.h"

bool logger(HttpRequest request, MiddlewareHandler *n);
bool fileLogger(HttpRequest request, MiddlewareHandler *n);

#endif