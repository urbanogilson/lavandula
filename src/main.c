#include "lavandula.h"

Page home() {
    Page p = page("Home");

    Text *t = text(&p, "Hello, World!");
    setTextSize(t, TEXT_XXL);
    setTextColour(t, COLOUR_RED);

    Box *b = box(&p, 80, 80);

    UIElement e = textRaw("Hello inside the box");
    putInBox(b, e);

    linkTo(&p, "Go to: Help", "http://127.0.0.1:3002/help");

    return p;
}

Page help() {
    Page p = page("Help");
    Text *t = text(&p, "This is the help page!");
    setTextSize(t, TEXT_XXL);

    linkTo(&p, "Back", "http://127.0.0.1:3002/");

    return p;
}

void registerRoutes(App *app) {
    route(&app->server.router, HTTP_GET, "/", home);
    route(&app->server.router, HTTP_GET, "/help", help);
}

int main() {
    App app = init(3002);
    registerRoutes(&app);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}