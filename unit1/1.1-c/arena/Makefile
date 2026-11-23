CC		= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all

.PHONY: all test clean

all: test_arena

test_arena: test_arena.c arena.c arena.h
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ test_arena.c arena.c

test: test_arena
	./test_arena

clean:
	rm -f test_arena

