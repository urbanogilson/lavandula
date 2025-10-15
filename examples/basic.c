#include "lavandula.h"

appRoute(home) {
    return ok("Hello, World", TEXT_PLAIN);
}

int main() {
    App app = createApp();
    root(&app, home);

    runApp(&app);
}