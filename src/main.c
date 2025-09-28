#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "cli.h"

Page home() {
    Page p = page("Home");

    Box *b = box(140, 200);
    putInPage(&p, b->element);
    boxBorder(b, COLOUR_BLACK, 2);

    boxPadding(b, paddingFrom(20, 10, 10, 40));
    boxMargin(b, margin(20, 20, 20, 20));

    Column *mainColumn = column();
    putInBox(b, mainColumn->element);

    Text *name = text("Ashton James");
    textSize(name, TEXT_XL);
    textBold(name);
    putInColumn(mainColumn, name->element);

    Text *info = text("I am a Software Developer");
    textSize(info, TEXT_S);
    putInColumn(mainColumn, info->element);

    Link *l = linkTo("http://127.0.0.1:3002/help", "Go to About");
    putInPage(&p, l->element);

    return p;
}

Page help() {
    Page p = page("Help");

    Text *t = text("This is the help page!");
    putInPage(&p, t->element);

    Link *l = linkTo("http://127.0.0.1:3002/", "Back to Home");
    putInPage(&p, l->element);

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

    App app = init(3002);

    route(&app.server.router, HTTP_GET, "/", home);
    route(&app.server.router, HTTP_GET, "/help", help);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}