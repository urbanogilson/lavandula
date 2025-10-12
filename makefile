SRCS = $(shell find src -name "*.c")

TEST_SRCS = $(wildcard test/*.c)
CFLAGS = -Wall -Wextra -lsqlite3 -Isrc -lssl -lcrypto

all:
	mkdir -p build
	gcc $(SRCS) $(CFLAGS) -o build/lavu

test:
	mkdir -p build
	gcc $(filter-out src/main.c, $(SRCS)) $(TEST_SRCS) $(CFLAGS) -o build/test_runner
	./build/test_runner

install:
	cp build/lavu /usr/local/bin/lavandula

clean:
	rm -rf build

.PHONY: all test install clean