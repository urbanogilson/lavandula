#include "include/lavandula.h"

HttpResponse home(AppContext ctx) {
    return ok("Hello, World!");
}

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    useBasicAuth(&builder);
    useMiddleware(&builder, basicAuth);

    App app = build(builder);

    addBasicCredentials(&app.auth, "admin", "password");

    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);

    if (argc < 2) {
        printf("usage: lavu <command> [options]\n");
        return 1;
    }

    char *option = argv[1];

    if (strcmp(option, "new") == 0) {
        if (argc < 3) {
            printf("error: expected project name after 'new'\n");
            return 1;
        }

        char *projectName = argv[2];
        return newProject(projectName);
    } else if (strcmp(option, "run") == 0) {
        return runProject();
    } else if (strcmp(option, "help") == 0) {
        return help();
    } else if (strcmp(option, "--version") == 0 || strcmp(option, "-v") == 0) {
        return version();
    } else if (strcmp(option, "migrate") == 0) {
        return migrate();
    } else {
        return unknownCommand(option);
    }
}