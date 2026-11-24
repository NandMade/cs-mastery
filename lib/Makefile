CC			= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g -MMD -MP
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all

.PHONY: all test clean

all: test_int_math

test_int_math: test_int_math.o int_math.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

test: test_int_math
	./test_int_math
clean:
	rm -f test_mathx *.o *.d

-include $(wildcard *.d)
