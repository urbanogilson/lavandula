#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lavandula.h"

HttpResponse getTodos(AppContext ctx) {
    DbContext db = *ctx.dbContext;
    DbResult *result = dbQueryRows(&db, "select * from Todos");
    if (!result) {
        return internalServerError("Failed to query database");
    }

    for (int i = 0; i < result->row_count; i++) {
        DbRow *row = &result->rows[i];
        printf("Row %d:\n", i);
        for (int j = 0; j < row->col_count; j++) {
            printf("  %s: %s\n", row->col_names[j], row->col_values[j]);
        }
    }

    return ok("ok");
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

    AppBuilder builder = createBuilder();
    usePort(&builder, 8080);
    useCorsPolicy(&builder, corsAllowAll());
    useSqlLite3(&builder, "todo.db");

    useEnvironment(&builder, DEVELOPMENT);

    if (isDevelopment(&builder)) {
        useVerboseLogging(&builder);
        useHttpsRedirect(&builder);
    }

    CorsConfig policy = corsPolicy();
    allowAnyMethod(&policy);
    allowAnyOrigin(&policy);

    useCorsPolicy(&builder, policy);

    App app = build(builder);
    get(&app, "/todos", getTodos);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}