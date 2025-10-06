#ifndef sql_h
#define sql_h

#include <stdbool.h>

typedef void (*RowCallback)(int colCount, char **colNames, char **colValues, void *userData);

typedef struct {
    int col_count;
    char **col_names;
    char **col_values;
} DbRow;

typedef struct {
    int row_count;
    DbRow *rows;
} DbResult;

typedef enum {
    SQLITE,
} SqlDbType;

typedef struct {
    SqlDbType type;

    // if type is SQLITE, connection is sqlite3*
    void *connection;
} DbContext;

DbContext *createSqlLite3DbContext(char *dbPath);

bool dbExec(DbContext *db, const char *query);
DbResult *dbQueryRows(DbContext *db, const char *query);

#endif