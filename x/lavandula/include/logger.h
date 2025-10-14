#ifndef logger_h
#define logger_h

#include "http.h"
#include "router.h"
#include "middleware.h"

HttpResponse logger(RequestContext context, MiddlewareHandler *n);
HttpResponse fileLogger(RequestContext context, MiddlewareHandler *n);

#endif