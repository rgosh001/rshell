#flags for compling from hw specs
CFLAS = -Wall -Werror -ansi -pedantic

all: rshell ls

rshell:
	mkdir bin
	g++ $(CFLAGS) src/main.cpp  -o bin/rshell

ls:
	g++ $(CFLAGS) src/ls.cpp  -o bin/ls

clean:
	rm -rf bin
