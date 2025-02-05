CC = gcc
CFLAGS = -Wall -Werror
SRC = complex.c solve.c my_prog.c
OBJ = $(patsubst %.c, %.o, $(SRC))

my_prog.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f my_prog.x
