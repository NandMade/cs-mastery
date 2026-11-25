CC			= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g -MMD -MP -I ~/learning/lib
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all
LIB 		?= ~/learning/lib
.PHONY: all test clean

all: test_vec

test_vec: test_vec.o vec.o int_math.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

int_math.o: $(LIB)/int_math.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

test: test_vec

clean:
	rm -f test_vec *.o *.d

-include $(wildcard *.d)
