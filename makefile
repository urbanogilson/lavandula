SRCS = $(wildcard src/*.c)
CFLAGS = -Wall -Wextra

all:
	gcc $(SRCS) $(CFLAGS) -o a