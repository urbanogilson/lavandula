SRCS = $(wildcard src/*.c)
CFLAGS = -Wall -Wextra

all:
	gcc $(SRCS) $(CFLAGS) -o build/lavu

install:
	cp build/lavu /usr/local/bin/lavandula
