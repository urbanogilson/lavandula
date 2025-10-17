#include "include/lavandula.h"

appRoute(home, ctx) {
    char *body = jsonStringify(ctx.body);
    return ok(body, TEXT_PLAIN);
}

int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 3000);

    useGlobalMiddleware(&builder, consoleLogger);

    App app = build(builder);

    Route rootRoute = root(&app, home);
    useLocalMiddleware(&rootRoute, validateJsonBody);

    runApp(&app);
}

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("usage: lavu <command> [options]\n");
//         return 1;
//     }

//     char *option = argv[1];

//     if (strcmp(option, "new") == 0) {
//         if (argc < 3) {
//             printf("error: expected project name after 'new'\n");
//             return 1;
//         }

//         char *projectName = argv[2];
//         return newProject(projectName);
//     } else if (strcmp(option, "run") == 0) {
//         return runProject();
//     } else if (strcmp(option, "build") == 0) {
//         return buildProject();
//     } else if (strcmp(option, "help") == 0) {
//         return help();
//     } else if (strcmp(option, "--version") == 0 || strcmp(option, "-v") == 0) {
//         return version();
//     } else {
//         return unknownCommand(option);
//     }
// }