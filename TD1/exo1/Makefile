CC = gcc
CFLAGS = -Wall -Werror

SRC = simulation.c heun-euler.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all: clean simulation.x

simulation.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)