CC = g++
CFLAS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: 
	mkdir rshell/bin
	$(CC) $(CFLAGS) src/main.cpp -o bin/rshell
