#ifndef auth_h
#define auth_h

#include "http.h"
#include "router.h"
#include "middleware.h"

HttpResponse basicAuth(AppContext context, MiddlewareHandler *n);

#endif