#ifndef logger_h
#define logger_h

#include "http.h"
#include "router.h"
#include "middleware.h"

bool logger(AppContext context, MiddlewareHandler *n);
bool fileLogger(AppContext context, MiddlewareHandler *n);

#endif