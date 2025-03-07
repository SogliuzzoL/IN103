include ../Makefile.common

FILES=set-packing.c

EXE=$(patsubst %.c,%.x, $(FILES))

CC=gcc
CFLAGS=-Wall -Werror -I$(INC)
LDFLAGS=-L$(LIB) -lin103

all: $(EXE)

%.x: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test: $(EXE)
	@for i in 1 2 3; do 						\
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
	@rm -f tests/*~

realclean: clean
	@rm -f $(EXE)
