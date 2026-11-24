CC			= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g -MMD -MP -I ~/learning/lib
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all

.PHONY: all test clean

all: test_vec

test_vec: test_vec.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

test: test_vec

clean:
	rm -f test_vec *.o *.d

-include $(wildcard *.d)
