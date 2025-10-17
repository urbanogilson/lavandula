#include "lavandula.h"

appRoute(home, ctx) {
    return ok("Hello, World!", TEXT_PLAIN);
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

    return 0;
}