#ifndef logger_h
#define logger_h

#include "http.h"
#include "router.h"

HttpResponse logger(HttpRequest request, Controller controller);

#endif