#include <stdio.h>

#include "lavandula.h"

HttpResponse test() {
    return ok("Ok from test!");
}


HttpResponse idx() {
    return ok("Ok from index!");
}

HttpResponse notFound() {

}

int main() {
    App app = init(3000);

    route(&app.server.router, HTTP_GET, "/", idx);
    route(&app.server.router, HTTP_GET, "/test", test);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}