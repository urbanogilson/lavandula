#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *readFile(const char *path) {
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        printf("unable to open file: %s\n", path);
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    int sz = ftell(fptr);
    rewind(fptr);

    char *buff = malloc(sz + 1);
    if (!buff) {
        fclose(fptr);
        return NULL;
    }

    fread(buff, 1, sz, fptr);
    buff[sz] = '\0';
    fclose(fptr);

    return buff;
}