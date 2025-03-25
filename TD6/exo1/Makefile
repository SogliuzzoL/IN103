INC=$(HOME)/Library/libin103-1.4.2/include
LIB=$(HOME)/Library/libin103-1.4.2/source

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: muddy-city.x

%.x: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.o

realclean: clean
	rm -f *.x
