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

```
./tests:

exec.script

```

How to run file
---------------
Depending on Operatiing System, OS X vs Unix, program is compiled with the `#include <wait.h>` library.

OS X will not compile but will need the removal of the `#include <wait.h>` library call. 


Once you have cloned the directory to your local machine, follow the directions below:
--------------------------------------------------------------------------------------
1. `cd into `rshell`

2. call `make`

3. `cd` into `bin`

4. call `rshell`

5. Can also do step 3 & 4 by calling `bin/rshell` instead

RShell will now open up instead of BASH and you can execute almost all to nothing commands as included in the regular terminal.


Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell."

- It will offer similarities such as the normal BASH Command shell.

- Execute the command of ls to a file (with given instructions above)

- Have special built in command "exit" to exit RSHELL and return to your local SHELL


Bugs
---
1. `exit` commands works 75% of the time under normal use and testing
