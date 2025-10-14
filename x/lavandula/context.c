#include "include/context.h"
#include "include/app.h"

RequestContext requestContext(App *app, HttpRequest request) {
    RequestContext context = {
        .app = app,
        .request = request,
        .db = app->dbContext
    };

    return context;
}