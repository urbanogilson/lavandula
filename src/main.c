#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "version.h"

HttpResponse home(HttpRequest _) {
    return ok("Welcome to Lavandula!");
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        char *option = argv[1];
        if (strcmp(option, "new") == 0) {
            if (argc < 3) {
                printf("error: expected project name after 'new'\n");
                return 1;
            }

            newProject(argv[2]);

            return 0;
        } else if (strcmp(option, "run") == 0) {
            runProject();
            return 0;
        } else if (strcmp(option, "help") == 0) {
            printf("Lavandula CLI\n");
            printf("Usage:\n");
            printf("  lavu new <project_name>   Create a new Lavandula project\n");
            printf("  lavu run                  Run the Lavandula project\n");
            printf("  lavu help                 Show this help message\n");
            return 0;
        } else if (strcmp(option, "--version") == 0 || strcmp(option, "-v") == 0) {
            printf("Lavandula version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
            return 0;
        } else {
            printf("error: unknown option '%s'\n", option);
            printf("Use 'lavu help' to see available commands.\n");
            // return 1;

        }
    }

    // JsonBuilder jBuilder = jsonBuilder();
    // jsonAddString(&jBuilder, "name", "This is a task!");
    // jsonAddInteger(&jBuilder, "age", 30);

    // jsonPrint(&jBuilder);

    // char *x = jsonStringify(&jBuilder);

    // freeJsonBuilder(&jBuilder);

    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);
    useCorsPolicy(&builder, corsAllowAll());

    useEnvironment(&builder, ENV_DEVELOPMENT);

    if (isDevelopment(&builder)) {
        useVerboseLogging(&builder);
        useHttpsRedirect(&builder);
    }

    // CorsConfig policy = corsPolicy();
    // allowAnyMethod(&policy);
    // allowAnyOrigin(&policy);

    // useCorsPolicy(&builder, policy);


    App app = build(builder);

    root(&app, home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}