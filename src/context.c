#include "context.h"

AppContext appContext(HttpRequest request) {
    AppContext context;
    context.request = request;
    
    return context;
}