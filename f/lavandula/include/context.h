#ifndef context_h
#define context_h

#include "sql.h"
#include "http.h"

typedef struct App App; 

typedef struct {
    App *app;

    DbContext *dbContext;
    HttpRequest request;
} AppContext;

AppContext appContext(App *app, HttpRequest request);

#endif