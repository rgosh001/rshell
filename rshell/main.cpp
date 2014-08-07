#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

using namespace std;
int main()
{
	int child_pid;  
	int parent_pid = getppid();
	int status = 0;
	istringstream iss;
	string usrinput;

	//gets local machine name
	char hostname[128];
	gethostname(hostname, sizeof hostname);

	//prints out username of current user along with local machine name
	cout << getlogin() << "@" << hostname << "$ ";

	getline(cin, usrinput);
	string commandName, argument1, argument2;
	
	//function finds where the '#' index is at
	int poundIndex = -1;
	for (int i = 0; i < usrinput.size(); ++i)
	{
		if(usrinput.at(i) == '#')
		{
			poundIndex = i;
		}
	}

	//takes poundIndex and uses the erase function to remove the comments
	//so that the program will take in the command name and arguement(s)
	if (poundIndex != -1)
	{
		usrinput.erase(poundIndex, usrinput.size()-1);
	}
	
	//separates the strings into the vector
	iss.str(usrinput);
	string val;
	vector<string> commands;
	while(iss >> val)
	{
		if (val == "exit")
		{
			return 0;
		}
		commands.push_back(val);
	}
	
	//allocating memory for the array
	int size = commands.size();
	char** cp;
	cp = new char*[size * sizeof(char*)];
	
	//copies command and argument(s) to array for EXECV()
	for (int i = 0; i < size; ++i)
	{
		string str2 = commands.at(i);

		if (i == 0)
		{
			string str1 = "/usr/bin/";
			str2 = str1.append(str2);
			cout << str2<< endl;
		}
		
		cp[i] = new char[str2.length() + 1];
		strcpy(cp[i], str2.c_str());
		cout << i << " " << cp[i] << endl;
	}

	//checks for array values
	/*for (int i = 0; i < size; ++i)
	{
		cout << "Array at " << i << ": " << cp[i] << endl;
	}*/

	//start of the forking process
	child_pid = fork();
	if (child_pid == 0)
	{
		//child process
		if (execv(cp[0], cp) == -1)
		{
			perror("EXECLV FAILED: ");
			exit(0);
		}
		else
		{
			execv(cp[0], cp);
		}
	}
	else
	{
		wait(&status);
		exit(0);
	}
	return 0;
}
