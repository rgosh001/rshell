Licensing Information: READ LICENSE

Project source can be downloaded from https://github.com/rgosh001/

Author List
-----------
Mike Izbicki
Rashid Goshtasbi

All other known bugs and fixes can be sent to rgosh001@ucr.edu
Reported bugs/fixes will be submitted to correction.

File List
---------
Makefile
main.cpp
LICENSE
README.md
exec.script

Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: HERE[http://linuxgazette.net/111/ramankutty.html]
This program is developed to write a simple command shell called "RShell."
	It will print a command promt
	Read in a command on one line.
	Execute the command
		Take in & function calls
	Have special built in command "exit"
	Take in comments followed from an # sign

Bugs:
	1)Random erros once in a while with message "ls: AllocZone"
	2)Sometimes shows bad adress error
	3)Will show bad address error but will work the next time around
		(No known segmentation faults found through GDB)
	4)May get memory allocation error due to local memory allocation availability
		and/or segmetation fault.
			-with newly updated respository, likeliness of not occuring has increased to
			a knowledge of 100%;
	5)	Depending on commands inputed from the user, they will not be supported due to
		the location of their directory on their local machine
