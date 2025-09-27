#ifndef ui_h
#define ui_h

typedef struct {
    int x;
} WebContext;

WebContext newContext();
void freeContext(WebContext *context);

#endif