#include "../src/include/lavandula.h"

#include "include/lavandula.h"

HttpResponse home(AppContext ctx) {
    return ok("Hello, World!");
}

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    useBasicAuth(&builder);

    App app = build(builder);

    addBasicCredentials(&app.auth, "admin", "password");

    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);
}