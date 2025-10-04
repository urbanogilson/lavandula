#include "../../src/lavandula.h"
#include "controllers/home.c"

void registerRoutes(App app) {
    root(&app, home);
}
