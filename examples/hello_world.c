#include "lavandula.h"

HttpResponse home(RequestContext ctx) {
    return ok("Hello, World!");
}

int main() {
    // Initialize the application builder
    AppBuilder builder = createBuilder();
    
    // Build the application
    App app = build(builder);

    // Define routes
    get(&app, "/home", home);

    // Run the application
    runApp(&app);

    // Cleanup leftover resources
    cleanupApp(&app);

    return 0;
}