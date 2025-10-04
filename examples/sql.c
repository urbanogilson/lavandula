#include "lavandula.h"

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

Todo rowToTodo(DbRow *row) {
    Todo todo = {
        .name = strdup(row->col_values[0]),
        .id = atoi(row->col_values[1])
    };

    return todo;
}

HttpResponse getTodos(AppContext ctx) {
    DbResult *result = dbQueryRows(ctx.dbContext, "select * from Todos");
    if (!result) {
        return internalServerError("Failed to query database");
    }

    JsonBuilder *root = jsonBuilder();

    JsonArray array = jsonArray();
    jsonPutArray(root, "todos", &array);

    for (int i = 0; i < result->row_count; i++) {
        Todo todo = rowToTodo(&result->rows[i]);
        jsonArrayAppend(&array, todoToJson(todo));
    }

    char *json = jsonStringify(root);
    freeJsonBuilder(root);

    return ok(json);
}

int main() {
    AppBuilder builder = createBuilder();
    useSqlLite3(&builder, "todo.db");

    App app = build(builder);

    get(&app, "/todos", getTodos);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}