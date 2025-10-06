#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
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

bool dbExec(DbContext *db, const char *query) {
    char *err_msg = NULL;
    if (sqlite3_exec((sqlite3 *)db->connection, query, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
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

    int col_count = sqlite3_column_count(stmt);

    int capacity = 10;
    int row_count = 0;
    DbRow *rows = malloc(sizeof(DbRow) * capacity);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (row_count >= capacity) {
            capacity *= 2;
            rows = realloc(rows, sizeof(DbRow) * capacity);
        }

        DbRow *row = &rows[row_count];
        row->col_count = col_count;

        row->col_names = malloc(sizeof(char*) * col_count);
        row->col_values = malloc(sizeof(char*) * col_count);

        for (int i = 0; i < col_count; i++) {
            row->col_names[i] = strdup(sqlite3_column_name(stmt, i));
            const char *val = (const char *)sqlite3_column_text(stmt, i);
            row->col_values[i] = val ? strdup(val) : strdup("NULL");
        }

        row_count++;
    }

    sqlite3_finalize(stmt);

    DbResult *result = malloc(sizeof(DbResult));
    result->row_count = row_count;
    result->rows = rows;

    return result;
}

bool dbClose(DbContext *db) {
    if (db->type == SQLITE) {
        sqlite3_close((sqlite3 *)db->connection);
    }

    return true;
}