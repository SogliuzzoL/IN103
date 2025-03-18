CC=gcc
CFLAGS=-Wall -Werror -I$(HOME)/Library/libin103-1.2/include
LDFLAGS=-L$(HOME)/Library/libin103-1.2/source -lin103

all: maze.x

%.x: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.o

realclean: clean
	rm -f *.x
