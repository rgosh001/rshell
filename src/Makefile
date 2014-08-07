CFLAS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: main.o
	mkdir bin
	g++ $(CFLAGS) main.cpp  -o bin/rshell

clean:
	rm -rf bin
