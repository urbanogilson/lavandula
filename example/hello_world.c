#include "../src/lavandula.h"

Page home() {
    Page p = page("Home");
    text(&p, "Hello, World!");

    return p;
}

int main() {
    App app = init(3000);

    route(&app.server.router, HTTP_GET, "/", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}