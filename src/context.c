#include "include/context.h"

RequestContext requestContext(App *app, HttpRequest request) {
    RequestContext context;
    context.app = app;
    context.request = request;

    return context;
}