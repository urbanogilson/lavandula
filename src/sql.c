#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "include/sql.h"

DbContext *createSqlLite3DbContext(char *dbPath) {
    DbContext *context = malloc(sizeof(DbContext));
    if (!context) return NULL;

    context->type = SQLITE;

    sqlite3 *db;
    int rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    context->connection = db;

    return context;
}

bool dbExec(DbContext *db, const char *query, ...) {
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2((sqlite3 *)db->connection, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg((sqlite3 *)db->connection));
        return false;
    }
    
    va_list args;
    va_start(args, query);
    
    int paramCount = sqlite3_bind_parameter_count(stmt);
    for (int i = 1; i <= paramCount; i++) {
        char *param = va_arg(args, char*);
        if (param) {
            sqlite3_bind_text(stmt, i, param, -1, SQLITE_STATIC);
        } else {
            sqlite3_bind_null(stmt, i);
        }
    }
    
    va_end(args);
    
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg((sqlite3 *)db->connection));
        return false;
    }
    
    return true;
}

DbResult *dbQueryRows(DbContext *db, const char *query) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2((sqlite3 *)db->connection, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare query: %s\n", sqlite3_errmsg((sqlite3 *)db->connection));
        return NULL;
    }

    int colCount = sqlite3_column_count(stmt);

    int capacity = 10;
    int rowCount = 0;
    DbRow *rows = malloc(sizeof(DbRow) * capacity);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (rowCount >= capacity) {
            capacity *= 2;
            rows = realloc(rows, sizeof(DbRow) * capacity);
        }

        DbRow *row = &rows[rowCount];
        row->colCount = colCount;

        row->colNames = malloc(sizeof(char*) * colCount);
        row->colValues = malloc(sizeof(char*) * colCount);

        for (int i = 0; i < colCount; i++) {
            row->colNames[i] = strdup(sqlite3_column_name(stmt, i));
            const char *val = (const char *)sqlite3_column_text(stmt, i);
            row->colValues[i] = val ? strdup(val) : strdup("NULL");
        }

        rowCount++;
    }

    sqlite3_finalize(stmt);

    DbResult *result = malloc(sizeof(DbResult));
    result->rowCount = rowCount;
    result->rows = rows;

    return result;
}

bool dbClose(DbContext *db) {
    if (db->type == SQLITE) {
        sqlite3_close((sqlite3 *)db->connection);
    }

    return true;
}