#include "../lavandula/include/lavandula.h"
#include "routes.h"

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    registerRoutes(&app);

    runApp(&app);

    return 0;
}
