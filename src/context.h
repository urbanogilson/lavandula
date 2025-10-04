#ifndef context_h
#define context_h

#include "sql.h"
#include "http.h"

typedef struct {
    DbContext *dbContext;
    HttpRequest request;
} AppContext;

AppContext appContext(HttpRequest request);

#endif