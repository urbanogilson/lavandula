#include "lavandula.h" 

// define a route for your app
appRoute(home) {
    return ok("Hello, World");
}

int main() {
    // initialise your app
    App app = createApp();

    // register a route in your app
    get(&app, "/home", home);

    // run the app
    runApp(&app);
}
