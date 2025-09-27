#include "ui.h"

WebContext newContext() {
    WebContext context = {
        .x = 1
    };

    return context;
}

void freeContext(WebContext *context) {
    if (!context) return;
}