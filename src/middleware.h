#ifndef middleware_h
#define middleware_h

typedef HttpResponse (*Middleware)(HttpRequest, Controller);

typedef struct MiddlewarePipeline {
    Middleware                *this;
    struct MiddlewarePipeline *next;
} MiddlewarePipeline;

#endif