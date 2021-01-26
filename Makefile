# /* +----------------------------------+ */
# /* |              GF256               | */
# /* |             Makefile             | */
# /* |   (c)copyright nitram147 2021    | */
# /* +----------------------------------+ */

CC=gcc
CFLAGS=-std=c99

all: test exp_log_tables_generator

test: test.o gf256.o
	$(CC) $(CFLAGS) -o test test.o gf256.o

exp_log_tables_generator: exp_log_tables_generator.c
	$(CC) $(CFLAGS) exp_log_tables_generator.c -o exp_log_tables_generator

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm test
	rm exp_log_tables_generator
	rm *.o
