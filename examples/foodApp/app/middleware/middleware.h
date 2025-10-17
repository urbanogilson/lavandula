#ifndef app_middleware_h
#define app_middleware_h

#include "../../lavandula/include/lavandula.h"

middleware(registerUserValidator, ctx, m);
middleware(loginUserValidator, ctx, m);

#endif