include ../Makefile.common

FILES=island.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: $(EXE)

%.x: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test: island.x
	./island.x < tests/test1.in

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
