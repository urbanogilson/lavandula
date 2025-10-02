SRCS = $(wildcard src/*.c)
CFLAGS = -Wall -Wextra

all:
	mkdir -p build
	gcc $(SRCS) $(CFLAGS) -o build/lavu

install:
	cp build/lavu /usr/local/bin/lavandula
