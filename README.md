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

./tests:

exec.script

ls.script
```

How to run file
---------------
Clone from respository presented in

Then `cd` into rshell

call make

then: bin/ls OR ls if you cd into bin.

Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell."

- It will print a command promt

- Read in a command on one line.

- Execute the command

- Take in & function calls

- Have special built in command "exit"

- Take in comments followed from an # sign

Bugs:
	1. Input: "bin/ls -Ra" will cause a streamline of random numbers. It is similar to the representive on bash but off.
	2. Formatting on bin/ls -l isn't formatted to the right correcty. Off by a few spaces.
	3. 
	4.
	5.
   6.
