CC=gcc
CFLAGS=-I.
DEPS = token.h lexer.h

all: monkey

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

monkey: token.o lexer.o main.o repl.o
	$(CC) -o monkey token.o lexer.o main.o

clean:
	rm token.o lexer.o main.o repl.o
