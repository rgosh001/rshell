Licensing Information: READ LICENSE

Project source can be downloaded from https://github.com/rgosh001/rshell.git

Author List
-----------
Mike Izbicki

Rashid Goshtasbi

All other known bugs and fixes can be sent to rgosh001@ucr.edu

Reported bugs/fixes will be submitted to correction.

File List
---------
```
.:

Makefile

LICENSE

README.md

./src

./tests

/src:

main.cpp

ls.cpp

hw3.cpp

./tests:

exec.script

ls.script

redirect.script
```

How to run file
---------------
Clone from respository presented in

Then `cd` into rshell

call make

then: bin/rshell OR ls if you cd into bin.

Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell."

- It will offer similarities such as a file redirection command would

- Execute the command of ls to a file

- Take in pipes and redirections for files

- Have special built in command "exit"


Bugs:
	1. Program isn't 100% working
   2. Program cannot execute execv in UNIX but will in Mac OS X in some scenarios
   3. Will compile
   4. Will work with <, >, >> on some occasions. Bug still in program, still trying to resolve due to transfer to compile in well server.
