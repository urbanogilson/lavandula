#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "version.h"

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
            return 1;

        }
    }

    // JsonBuilder jBuilder = jsonBuilder();
    // jsonAddString(&jBuilder, "name", "This is a task!");
    // jsonAddInteger(&jBuilder, "age", 30);

    // jsonPrint(&jBuilder);

    // // char *x = jsonStringify(&jBuilder);

    // freeJsonBuilder(&jBuilder);

    // return 0;

    // AppBuilder builder = createBuilder();
    // usePort(&builder, 8080);

    // // - PostgreSL, MySQL, SQLite integrations, etc
    // //    - build an actual mini backend with it
    // // - Look at Dependency Injection containers
    // // - CORS, Rate Limiting, etc
    // // - Static file serving
    // // - Session cookiess
    // // - ORM with JSON serialization and code generation
    // // - JSON scaffolding from CLI
    // //   - lavu model User name:string age:int
    // //   - generates User struct, JSON serialization, CRUD endpoints in user_controller.c


    // App app = build(builder);

    // root(&app, getTodos);
    // get(&app, "/todos", getTodos);

    // // printf("\nAvailable endpoints:\n");
    // // printf("  GET  /                    - API documentation\n");
    // // printf("  GET  /todos               - Get all todos\n");
    // // printf("  GET  /todos/summary       - Get todo statistics\n");
    // // printf("  POST /todos               - Create new todo\n");
    // // // printf("  GET  /health              - Health check\n");
    // // printf("\nTry these commands:\n");
    // // printf("  curl http://localhost:3000/\n");
    // // printf("  curl http://localhost:3000/todos\n");
    // // printf("  curl http://localhost:3000/demo\n");
    // // printf("  curl -X POST http://localhost:3000/todos\n");
    // // printf("\n");

    // runApp(&app);

    // cleanupApp(&app);

    return 0;
}