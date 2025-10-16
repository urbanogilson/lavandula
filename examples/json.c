#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"
#include "version.h"

typedef struct {
    char *name;
    int   id;
} Todo;

Json todoToJson(Todo todo) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutString(builder, "name", todo.name);
    jsonPutInteger(builder, "id", todo.id);

    return jsonObject(builder);
}

Todo *allTodos() {
    static Todo todos[3] = {
        {"Task 1", 1},
        {"Task 2", 2},
        {"Task 3", 3}
    };

    return todos;
}

appRoute(getTodos, ctx) {
    JsonBuilder *root = jsonBuilder();

    JsonArray array = jsonArray();
    jsonPutArray(root, "todos", &array);

    Todo *todos = allTodos();
    for (int i = 0; i < 3; i++) {
        jsonArrayAppend(&array, todoToJson(todos[i]));
    }

    char *json = jsonStringify(root);
    freeJsonBuilder(root);

    return ok(json, APPLICATION_JSON);
}

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    get(&app, "/todos", getTodos);

    runApp(&app);

    return 0;
}