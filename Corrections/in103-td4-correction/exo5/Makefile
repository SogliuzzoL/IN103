FILES=req.c

EXE=$(patsubst %.c, %.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(HOME)/Library/libin103-1.4/include
LDFLAGS=-L$(HOME)/Library/libin103-1.4/source -lin103 -lm

all: $(EXE)

req.x: read.o integer_streep.o req.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f *.x
