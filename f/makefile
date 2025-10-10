SRCS_LAVANDULA = $(filter-out lavandula/main.c, $(shell find lavandula -name "*.c"))

SRCS = app/app.c app/routes.c $(wildcard app/controllers/*.c)
CFLAGS = -Wall -Wextra -lsqlite3 -Isrc -Ilavandula/include

all:
	gcc $(SRCS) $(SRCS_LAVANDULA) $(CFLAGS) -o a
