CC			= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g -MMD -MP
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all

.PHONY: all test clean

all: test_int_math test_hash

test_int_math: test_int_math.o int_math.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

test_hash: test_hash.o hash.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

test: test_int_math test_hash
	./test_int_math
	./test_hash

clean:
	rm -f test_int_math test_hash *.o *.d

-include $(wildcard *.d)
