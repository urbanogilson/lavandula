#include "lavandula.h"

App init(int port) {
    App app = {
        .server = initServer(port)
    };

    return app; 
}

void runApp(App *app) {
    runServer(&app->server);
}

void cleanupApp(App *app) {
    if (!app) return;
    
    freeServer(&app->server);
}