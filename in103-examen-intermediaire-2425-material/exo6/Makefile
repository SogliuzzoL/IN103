include ../Makefile.common

FILES=interplay.c

EXE=$(patsubst %.c,%.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: $(EXE)

%.x: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test: $(EXE)
	@for i in 1 2 3 4; do 						\
		./$(EXE) < tests/test$$i.in | diff - tests/test$$i.out; \
		if [ $$? -eq 0 ]; then \
			echo "Test $$i: OK";\
		else \
			echo "Test $$i: KO"; \
		fi \
	done

clean:
	@rm -f *~
	@rm -f *.o

realclean: clean
	@rm -f $(EXE)
