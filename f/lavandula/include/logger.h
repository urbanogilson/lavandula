#ifndef logger_h
#define logger_h

#include "http.h"
#include "router.h"
#include "middleware.h"

HttpResponse logger(AppContext context, MiddlewareHandler *n);
HttpResponse fileLogger(AppContext context, MiddlewareHandler *n);

#endif