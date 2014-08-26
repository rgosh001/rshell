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

- It will offer similarities such as a ls command

- Execute the command of ls

- Take in & function calls

- Have special built in command "exit"


Bugs
---
1. Input: `bin/ls -Ra` will cause a streamline of random numbers. It is similar to the representive on bash but off.
2. Formatting on `bin/ls -l` isn't formatted to the right correcty. Off by a few spaces.
3. Bug when trying to use `-R` on a folder with more than 3 directories (in the works!)
4. Recursion still needs some fixing, found bugs with deep level `ls -R` commands
5. Can't call `ls` if you are within the `bin` directory
6.
