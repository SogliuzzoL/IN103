CC=gcc
CFLGAS=-Wall -Werror -I$(HOME)/Library/libin103-1.4.2/include
LDFLAGS=-L$(HOME)/Library/libin103-1.4.2/source -lin103

all: list-printer.x

list-printer.x: list-printer.o
	$(CC) $(CFLGAS) -o $@ $< $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLGAS) -c $<

clean:
	rm -f *~ *.o

realclean: clean
	rm -f *.x
