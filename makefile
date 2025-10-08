SRCS = $(wildcard src/*.c)

# temporary solution
LAVENDER_SRCS = $(wildcard src/lavender/*.c)
YAML_SRCS = $(wildcard src/yaml/*.c)
# --

TEST_SRCS = $(wildcard test/*.c)
CFLAGS = -Wall -Wextra -lsqlite3 -Isrc

all:
	mkdir -p build
	gcc $(SRCS) $(LAVENDER_SRCS) $(YAML_SRCS) $(CFLAGS) -o build/lavu

test:
	mkdir -p build
	gcc $(filter-out src/main.c, $(SRCS)) $(TEST_SRCS) $(CFLAGS) -o build/test_runner
	./build/test_runner

install:
	cp build/lavu /usr/local/bin/lavandula

clean:
	rm -rf build

.PHONY: all test install clean