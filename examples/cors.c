#include "../src/lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

int main() {
    AppBuilder builder = createBuilder();

    // defines a CORS policy
    CorsConfig policyBasicOne = corsPolicy();
    allowOrigin(&policyBasicOne, "www.example.com");
    allowMethod(&policyBasicOne, HTTP_GET);
    allowMethod(&policyBasicOne, HTTP_POST);

    // defines a forgiving CORS policy
    CorsConfig policyBasicTwo = corsPolicy();
    allowAnyMethod(&policyBasicTwo);
    allowAnyOrigin(&policyBasicTwo);
    
    // also defines a forgiving CORS policy
    CorsConfig policyAll = corsAllowAll();

    // adds the CORS policy to the application
    useCorsPolicy(&builder, policyAll);


    App app = build(builder);

    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}