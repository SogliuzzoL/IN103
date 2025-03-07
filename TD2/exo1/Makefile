CC = gcc
CFLAGS = -Wall -Werror -I$(HOME)/Library/libin103-1.4.2/include
SRC = list-printer.c
OBJ = $(patsubst %.c, %.o, $(SRC))
IN103 = -L$(HOME)/Library/libin103-1.4.2/source -lin103

list-printer.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(IN103)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o