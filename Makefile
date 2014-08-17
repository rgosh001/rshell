#flags for compling from hw specs
CFLAS = -Wall -Werror -ansi -pedantic

all: clean rshell ls old_rshell

rshell:
	mkdir bin
	g++ $(CFLAGS) src/hw3.cpp  -o bin/rshell

old_rshell:
	g++ $(CFLAGS) src/main.cpp  -o bin/old_rshell

ls:
	g++ $(CFLAGS) src/ls.cpp  -o bin/ls

clean:
	rm -rf bin
