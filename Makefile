CC = g++
CFLAS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: 
	$(CC) $(CFLAGS) src/main.cpp -o bin/rshell
