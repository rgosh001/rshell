#flags for compling from hw specs
CFLAS = -Wall -Werror -ansi -pedantic

all: rshell hw3-rshell ls old_rshell

install: all
	export PATH="~/bin:$(PATH)"
	cp -a ./bin ~/
   
rshell:
	([ ! -d bin ] && mkdir bin) || [ -d bin ]
	g++ $(CFLAGS) src/path.cpp  -o bin/rshell

hw3-rshell:
	g++ $(CFLAGS) src/hw3.cpp  -o bin/hw3-rshell

old_rshell:
	g++ $(CFLAGS) src/main.cpp  -o bin/og_rshell

ls:
	g++ $(CFLAGS) src/ls.cpp  -o bin/ls

clean:
	rm -rf bin
	rm -rf ~/bin
