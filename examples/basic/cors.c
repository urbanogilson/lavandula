#include "lavandula.h"

appRoute(home, ctx) {
    return ok("Hello, World!", TEXT_PLAIN);
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

    return 0;
}