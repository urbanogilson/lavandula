#ifndef lavandula_h
#define lavandula_h

#include "server.h"
#include "ui.h"

typedef struct {
    Server server;
} App;

App init(int port);

void runApp(App *app);
void cleanupApp(App *app);

#endif