#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "cli.h"

typedef struct {
    char *title;
} TodoItem;

HttpResponse getTodos(HttpRequest request) {
    return ok(request.resource);
}

HttpResponse createTodo(HttpRequest request) {
    return ok(request.resource);
}

HttpResponse someMiddleware(HttpRequest request, Controller controller) {
    if (true) {
        return badRequest("bad request");
    }

    return controller(request);
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

    AppBuilder builder = createBuilder();
    usePort(&builder, 3005);
    useMiddleware(&builder, someMiddleware);

    App app = build(builder);

    get(&app.server.router, "/getTodos", getTodos);
    post(&app.server.router, "/createTodo", createTodo);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}