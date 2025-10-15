#include "lavandula.h"

appRouteStatic(home, "home.html");

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