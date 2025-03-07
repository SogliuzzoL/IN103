include ../Makefile.common

FILES=is-pangram.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: $(EXE)

%.x: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test: is-pangram.x
	./is-pangram.x < tests/test1.in
	./is-pangram.x < tests/test2.in
	./is-pangram.x < tests/test3.in
	./is-pangram.x < tests/test4.in

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
