FILES=test-stree.c test-streep.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(HOME)/Library/libin103-1.4/include
LDFLAGS=-L$(HOME)/Library/libin103-1.4/source -lin103 -lm

all: $(EXE)

test-stree.x: integer_stree.o test-stree.o
	$(CC) -o $@ $^ $(LDFLAGS)

test-streep.x: integer_streep.o test-streep.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
