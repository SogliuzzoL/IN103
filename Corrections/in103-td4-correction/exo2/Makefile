CC=gcc
CFLAGS=-Wall -Werror -I$(HOME)/Library/libin103-1.4/include
LDFLAGS=-L$(HOME)/Library/libin103-1.4/source -lin103

all: maze-generator.x

%.x: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.o

realclean: clean
	rm -f *.x
