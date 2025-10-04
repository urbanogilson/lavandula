#include "../src/lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

HttpResponse notFound(HttpRequest _) {
    return response("Oops, this resource was not found...", HTTP_NOT_FOUND);
}

int main() {
    AppBuilder builder = createBuilder();

    usePort(&builder, 8080);
    useHttpsRedirect(&builder);
    useDotenv(".env");

    useMiddleware(&builder, logger);

    CorsConfig policy = corsPolicy();
    allowOrigin(&policy, "www.example.com");
    allowMethod(&policy, HTTP_GET);
    allowMethod(&policy, HTTP_POST);
    useCorsPolicy(&builder, policy);

    char *secretKey = env("SECRET_KEY");
    if (!secretKey) return 1;

    useEnvironment(&builder, DEVELOPMENT);

    if (isDevelopment(&builder)) {
        useVerboseLogging(&builder);
    }

    App app = build(builder);

    root(&builder, home);
    routeNotFound(&builder, notFound);
    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}