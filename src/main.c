#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "cli.h"

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

// Page help() {
//     Page p = page("Help");
//     Text *t = text(&p, "This is the help page!");
//     setTextSize(t, TEXT_XXL);

//     linkTo(&p, "Back", "http://127.0.0.1:3002/");

//     return p;
// }

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        char *option = argv[1];
        if (strcmp(option, "new") == 0) {
            if (argc < 3) {
                printf("error: expected project name after 'new'\n");
                return 1;
            }

            char *projectName = argv[2];
            newProject(projectName);

            return 0;
        }
    }

    App app = init(3002);

    route(&app.server.router, HTTP_GET, "/", home);
    // route(&app.server.router, HTTP_GET, "/help", help);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}