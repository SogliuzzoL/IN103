FILES=test-ht.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I../../../include -I. -std=c99
LDFLAGS=-L../../../source -lin103

all: $(EXE)

$(EXE): generic_hashtable.o test-ht.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
