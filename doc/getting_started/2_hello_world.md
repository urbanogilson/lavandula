# Hello World Example

This example starts a simple web server with a root endpoint defined. The web server will respond to requests for `/` with `Hello, World!`.

```c
#include "lavandula.h"

appRoute(home) {
    return ok("Hello, World", TEXT_PLAIN);
}

int main() {
    App app = createApp();
    get(&app, "/", home);

    runApp(&app);
}
```

You can run this application with the following command.

```bash
lavu run
```

Next: [App Routing](3_app_routing.md)