#include "../src/include/lavandula.h"

HttpResponse protectedRoute(AppContext ctx) {
    return ok("Hello, authenticated user! This is a protected route.");
}

int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);
    
    useMiddleware(&builder, basicAuth);

    App app = build(builder);

    get(&app, "/admin", protectedRoute);
    
    runApp(&app);
    
    cleanupApp(&app);

    return 0;
}