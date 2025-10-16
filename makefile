SRCS = $(shell find src -name "*.c")

TEST_SRCS = $(wildcard test/*.c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lsqlite3 -Isrc
TEST_CFLAGS = -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector-strong

LIB_SRCS = $(filter-out src/main.c src/cli.c, $(SRCS))
LIB_CFLAGS = -Wall -Wextra -Isrc
LIB_OBJS = $(patsubst src/%.c, build/%.o, $(LIB_SRCS))
OS = $(shell uname -s)

all:
	mkdir -p build
	$(CC) $(SRCS) $(CFLAGS) -o build/lavu

test:
	mkdir -p build
	$(CC) $(filter-out src/main.c, $(SRCS)) $(TEST_SRCS) $(CFLAGS) $(TEST_CFLAGS) -o build/test_runner
	./build/test_runner

static: $(LIB_OBJS)
	mkdir -p build
	ar rcs build/liblavu.a $(LIB_OBJS)

shared: $(LIB_OBJS)
	mkdir -p build
	gcc -shared -o build/liblavu.so $(LIB_OBJS) -lsqlite3 -Wl,-rpath,/usr/local/lib
	if [ "$(OS)" = "Darwin" ]; then \
		install_name_tool -id /usr/local/lib/liblavu.so build/liblavu.so; \
		otool -L build/liblavu.so; \
	fi

build/lavender/%.o: src/lavender/%.c
	mkdir -p build/lavender
	gcc -c $< $(LIB_CFLAGS) -o $@

build/yaml/%.o: src/yaml/%.c
	mkdir -p build/yaml
	gcc -c $< $(LIB_CFLAGS) -o $@

build/%.o: src/%.c
	mkdir -p build
	gcc -fPIC -c $< $(LIB_CFLAGS) -o $@

lib: static shared

install-libs: static shared
	cp build/liblavu.a build/liblavu.so /usr/local/lib
	cp liblavu.pc /usr/local/lib/pkgconfig/
	cp -R src/include /usr/local/include/lavandula

install:
	cp build/lavu /usr/local/bin/lavu

clean:
	rm -rf build

.PHONY: all test install clean
