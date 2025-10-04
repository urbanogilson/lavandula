#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "version.h"

// HttpResponse getTodos(HttpRequest _) {
//     return ok("");
// }

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

    JsonBuilder root = jsonBuilder();

    JsonArray todos = jsonArray();
    jsonPutArray(&root, "todos", &todos);

    JsonBuilder todo = jsonBuilder();
    jsonPutString(&todo, "name", "This is a task!");
    jsonPutInteger(&todo, "id", 30);

    jsonArrayAppend(&todos, jsonObject(&todo));

    char *x = jsonStringify(&root);
    printf("%s\n", x);
    
    freeJsonBuilder(&root);
    freeJsonBuilder(&todo);
    free(x);

    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);
    useCorsPolicy(&builder, corsAllowAll());

    useEnvironment(&builder, DEVELOPMENT);

    if (isDevelopment(&builder)) {
        useVerboseLogging(&builder);
        useHttpsRedirect(&builder);
    }

    // CorsConfig policy = corsPolicy();
    // allowAnyMethod(&policy);
    // allowAnyOrigin(&policy);

    // useCorsPolicy(&builder, policy);


    App app = build(builder);

    // get(&app, "/todos", getTodos);

    // runApp(&app);
    cleanupApp(&app);

    return 0;
}