#include "../../../src/lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}
