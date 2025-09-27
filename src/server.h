#ifndef server_h
#define server_h

#include "router.h"

typedef struct {
    Router router;
    
    int port;
    int fileDescriptor;
} Server;

Server initServer(int port);
void freeServer(Server *server);

void runServer(Server *Server);

#endif