CC = gcc
CFLAGS = -Wall -Werror
SRC = main.c convex.c points2d.c
OBJ = $(patsubst %.c, %.o, $(SRC))

main.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm main.x
