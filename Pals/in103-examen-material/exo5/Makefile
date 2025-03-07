include ../Makefile.common

FILES=inventory.c inventory-v2.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: $(EXE)

%.x: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test: inventory.x
	./inventory.x < tests/test1.in
#	./inventory.x < tests/test1.in | diff - tests/test1-v1.out

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
