CC = gcc
CFLAGS = -Wall -Werror
SRC = my_malloc.c my_main.c
OBJ = $(patsubst %.c, %.o, $(SRC))

my_main.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
