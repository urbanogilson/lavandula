#include "lavandula.h"

HttpResponse homePage(RequestContext _) {
    return ok("Hello, World!");
}

HttpResponse notFoundPage(RequestContext _) {
    return response("Oops, this resource was not found...", HTTP_NOT_FOUND);
}

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

HttpResponse getTodos(RequestContext ctx) {
    DbResult *result = dbQueryRows(ctx.db, "select * from Todos");
    if (!result) {
        return internalServerError("Failed to query database");
    }

    JsonBuilder *root = jsonBuilder();

    JsonArray array = jsonArray();
    jsonPutArray(root, "todos", &array);

    for (int i = 0; i < result->rowCount; i++) {
        DbRow *row = &result->rows[i];

        Todo todo = {
            .name = strdup(row->colValues[0]),
            .id = atoi(row->colValues[1])
        };
        
        jsonArrayAppend(&array, todoToJson(todo));
    }

    char *json = jsonStringify(root);
    freeJsonBuilder(root);

    return ok(json);
}

int main() {
    AppBuilder builder = createBuilder();

    usePort(&builder, 8080);
    useHttpsRedirect(&builder);
    useDotenv(".env");
    useSqlLite3(&builder, "todo.db");

    useMiddleware(&builder, logger);

    CorsConfig policy = corsPolicy();
    allowOrigin(&policy, "www.example.com");
    allowMethod(&policy, HTTP_GET);
    allowMethod(&policy, HTTP_POST);
    useCorsPolicy(&builder, policy);

    char *secretKey = env("SECRET_KEY");

    useEnvironment(&builder, DEVELOPMENT);

    if (isDevelopment(&builder)) {
        useVerboseLogging(&builder);
    }

    App app = build(builder);

    root(&app, homePage);
    routeNotFound(&app, notFoundPage);

    get(&app, "/todos", getTodos);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}