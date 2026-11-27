CC			= gcc
CFLAGS		= -std=c17 -Wall -Wextra -Wpedantic -g -MMD -MP -I ~/learning/lib
SANFLAGS	= -fsanitize=address,undefined -fno-sanitize-recover=all
LIB 		?= ~/learning/lib
.PHONY: all test clean valgrind

all: test_vec test_map

test_vec: test_vec.o vec.o int_math.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

test_map: test_map.o map.o hash.o
	$(CC) $(CFLAGS) $(SANFLAGS) -o $@ $^

int_math.o: $(LIB)/int_math.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

hash.o: $(LIB)/hash.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

test: test_vec test_map
	./test_vec
	./test_map

valgrind: test_vec_raw test_map_raw
	valgrind -q --leak-check=full --error-exitcode=1 ./test_vec_raw
	valgrind -q --lead-check=full --error-exitcode=1 ./test_map_raw

test_vec_raw: test_vec_raw.o vec_raw.o int_math_raw.o
	$(CC) $(CFLAGS) -o $@ $^

test_map_raw: test_map_raw.o map_raw.o hash_raw.o

int_math_raw.o: $(LIB)/int_math.c
	$(CC) $(CFLAGS) -c -o $@ $<

hash_raw.o: $(LIB)/hash.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_raw.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f test_vec test_vec_raw test_map test_map_raw *.o *.d

-include $(wildcard *.d)
