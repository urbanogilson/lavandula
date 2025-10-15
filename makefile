SRCS = $(shell find src -name "*.c")

TEST_SRCS = $(wildcard test/*.c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lsqlite3 -Isrc

all:
	mkdir -p build
	$(CC) $(SRCS) $(CFLAGS) -o build/lavu

test:
	mkdir -p build
	$(CC) $(filter-out src/main.c, $(SRCS)) $(TEST_SRCS) $(CFLAGS) -o build/test_runner
	./build/test_runner

install:
	cp build/lavu /usr/local/bin/lavu

clean:
	rm -rf build

.PHONY: all test install clean