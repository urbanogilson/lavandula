#include "lavandula.h"

appRoute(home, ctx) {
    return ok("Hello, World", TEXT_PLAIN);
}

int main() {
    App app = createApp();
    root(&app, home);

    runApp(&app);
}