#include "lavandula.h"

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    useLavender(&builder);

    LavenderSchemaParser parser = newSchemaParser("schema.lavender");
    parseSchema(&parser);

    App app = build(builder);

    // runApp(&app);
    cleanupApp(&app);

    return 0;

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
    } else {
        return unknownCommand(option);
    }
}