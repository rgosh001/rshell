Licensing Information: READ LICENSE
---
Project source can be downloaded from https://github.com/rgosh001/rshell.git
----

Author & Contributor List
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
```
```
/src:

main.cpp

ls.cpp

hw3.cpp

path.cpp
```
```
./tests:

exec.script

ls.script

redirect.script

path.script
```

How to run file
---------------
Depending on Operatiing System, OS X vs Unix, program is compiled with the `#include <wait.h>` library.

OS X will not compile but will need the removal of the `#include <wait.h>` library call. 

For full feature, please add current path to the rshell directory to your $PATH. This will enable you to use the ls features made in my personal ls shell.

Once you have cloned the directory to your local machine, follow the directions below:
--------------------------------------------------------------------------------------
1. `cd` into `bin`

2. call `rshell`

RShell will now open up instead of BASH and you can execute almost all to nothing commands as included in the regular terminal.


Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell."

- It will offer similarities such as the normal BASH Command shell.

- Execute the command of ls to a file (with given instructions above)

- Can call all commands of BASH with execv function

- Have special built in command "exit" to exit RSHELL and return to your local SHELL


Bugs
---
1. `exit` commands works 75% of the time under normal use and testing

2. `^C` works but when calling it from rshell with nothing running, will produce an error pertaining to a vector out of range. (GDB debugging still in progress)

