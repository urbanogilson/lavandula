#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "cli.h"


Page home() {
    Page p = page("Home");

    Text *name = text("The state has not changed!");
    textSize(name, TEXT_XL);
    textBold(name);

    putInPage(&p, name->element);

    State *state = newState(name, NULL);
    setState(state, "The state has changed!");
    
    return p;
}

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

    App app = init(3003);

    route(&app.server.router, HTTP_GET, "/", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}