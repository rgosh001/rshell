#flags for compling from hw specs
CFLAS = -Wall -Werror -ansi -pedantic

all: rshell

rshell:
	([ ! -d bin ] && mkdir bin) || [ -d bin ]
	g++ $(CFLAGS) src/main.cpp  -o bin/rshell

clean:
	rm -rf bin
