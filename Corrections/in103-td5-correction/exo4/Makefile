CC=gcc
CFLAGS=-Wall -Werror -I$(HOME)/Library/libin103-1.4/include
LDFLAGS=-L$(HOME)/Library/libin103-1.4/source -lin103

all: graph-coloring.x

%.x: %.o
	$(CC) $(CFLGAS) -o $@ $< $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLGAS) -c $<

clean:
	rm -f *~ *.o

realclean: clean
	rm -f *.x
