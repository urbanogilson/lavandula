#ifndef lavandula_h
#define lavandula_h

#include "cli.h"
#include "server.h"
#include "dotenv.h"
#include "middleware.h"
#include "logger.h"
#include "lavandula_test.h"
#include "json.h"
#include "cors.h"
#include "environment.h"

typedef struct {
    Server             server;
    int                port;
    bool               verboseLogging; 
    bool               useHttpsRedirect;
    char              *environment;

    MiddlewareHandler middleware;
    CorsConfig         corsPolicy;
} App;

typedef struct {
    App app;
} AppBuilder;

AppBuilder createBuilder();

void usePort(AppBuilder *builder, int port);
void useMiddleware(AppBuilder *builder, MiddlewareFunc);
void useVerboseLogging(AppBuilder *builder);
void useDotenv(char *path);
void useCorsPolicy(AppBuilder *builder, CorsConfig);
void useDefaultCorsPolicy(AppBuilder *builder);
void useHttpsRedirect(AppBuilder *builder);
void useEnvironment(AppBuilder *builder, char *env);

bool isDevelopment(AppBuilder *builder);
bool isProduction(AppBuilder *builder);
bool isTesting(AppBuilder *builder);

App build(AppBuilder builder);

void runApp(App *app);
void cleanupApp(App *app);

void get(App *app, char *path, Controller controller);
void post(App *app, char *path, Controller controller);
void put(App *app, char *path, Controller controller);
void delete(App *app, char *path, Controller controller);
void patch(App *app, char *path, Controller controller);
void options(App *app, char *path, Controller controller);

// defines a special route for handling 404s
void   routeNotFound(App *app,  Controller controller);

// defines a special route for handling the root path
void   root(App *app, Controller controller);


#endif