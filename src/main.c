#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"

typedef struct {
    char *name;
    int age;
} Todo;

HttpResponse getTodos(HttpRequest _) {
    return ok("Hello, World!");
}

void todoToJson(Todo todo, JsonBuilder *builder) {
    jsonAddString(builder, "name", todo.name);
    jsonAddInteger(builder, "age", todo.age);
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
        }
    }

    JsonBuilder jBuilder = jsonBuilder();
    jsonAddString(&jBuilder, "name", "This is a task!");
    jsonAddInteger(&jBuilder, "age", 30);

    jsonPrint(&jBuilder);

    // char *x = jsonStringify(&jBuilder);

    freeJsonBuilder(&jBuilder);

    return 0;

    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);

    // - PostgreSL, MySQL, SQLite integrations, etc
    //    - build an actual mini backend with it
    // - Look at Dependency Injection containers
    // - CORS, Rate Limiting, etc
    // - Static file serving
    // - Session cookiess
    // - ORM with JSON serialization and code generation
    // - JSON scaffolding from CLI
    //   - lavu model User name:string age:int
    //   - generates User struct, JSON serialization, CRUD endpoints in user_controller.c


    App app = build(builder);

    root(&app, getTodos);
    get(&app, "/todos", getTodos);

    // printf("\nAvailable endpoints:\n");
    // printf("  GET  /                    - API documentation\n");
    // printf("  GET  /todos               - Get all todos\n");
    // printf("  GET  /todos/summary       - Get todo statistics\n");
    // printf("  POST /todos               - Create new todo\n");
    // // printf("  GET  /health              - Health check\n");
    // printf("\nTry these commands:\n");
    // printf("  curl http://localhost:3000/\n");
    // printf("  curl http://localhost:3000/todos\n");
    // printf("  curl http://localhost:3000/demo\n");
    // printf("  curl -X POST http://localhost:3000/todos\n");
    // printf("\n");

    runApp(&app);

    cleanupApp(&app);

    return 0;
}