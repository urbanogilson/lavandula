#include "include/context.h"

AppContext appContext(App *app, HttpRequest request) {
    AppContext context;
    context.app = app;
    context.request = request;

    return context;
}