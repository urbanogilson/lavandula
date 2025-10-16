#include "../lavandula/include/lavandula.h"

#include "controllers/controllers.h"
#include "middleware/middleware.h"

void registerRoutes(App *app) {
    Route registerUserRoute = get(app, "/api/register", registerUser);
    useLocalMiddleware(&registerUserRoute, registerUserValidator);

    Route loginUserRoute = post(app, "/api/login", loginUser);
    useLocalMiddleware(&loginUserRoute, loginUserValidator);

    Route logoutUserRoute = post(app, "/api/logout", logoutUser);
    useLocalMiddleware(&logoutUserRoute, logoutUserValidator);
}