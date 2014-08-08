#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <vector>

using namespace std;
int main()
{
	istringstream iss;
	string usrinput;

	//gets local machine name
	char hostname[128];
	gethostname(hostname, sizeof hostname);

	bool runShell = true;
	while(runShell)
	{
		istringstream iss;
		//prints out username of current user along with local machine name
		cout << getlogin() << "@" << hostname << "$ ";

		getline(cin, usrinput);
		//function finds where the '#' index is at
		int poundIndex = -1;
		int andSignIndex;
		bool andSign = false;
		for (int i = 0; i < usrinput.size(); ++i)
		{
			if(usrinput.at(i) == '#')
			{
				poundIndex = i;
				break;
			}
			if (usrinput.at(i) == '&')
			{
				andSign = true;
				andSignIndex = i;
				break;
			}
		}

		//takes poundIndex and uses the erase function to remove the comments
		//so that the program will take in the command name and arguement(s)
		if (poundIndex != -1)
		{
			usrinput.erase(poundIndex, usrinput.size());
		}
	
		//removes "&" so that the command line doesn't produce an error
		if (andSign)
		{
			usrinput.erase(andSignIndex, andSignIndex + 1);
		}
		while (usrinput == "")
		{
			cout << getlogin() << "@" << hostname << "$ ";
			getline(cin, usrinput);
			//function finds where the '#' index is at
			int poundIndex = -1;
			int andSignIndex;
			bool andSign = false;
			for (int i = 0; i < usrinput.size(); ++i)
			{
				if(usrinput.at(i) == '#')
				{
					poundIndex = i;
					break;
				}
				if (usrinput.at(i) == '&')
				{
					andSign = true;
					andSignIndex = i;
					break;
				}
			}

			//takes poundIndex and uses the erase function to remove the comments
			//so that the program will take in the command name and arguement(s)
			if (poundIndex != -1)
			{
				usrinput.erase(poundIndex, usrinput.size());
			}
		
			//removes "&" so that the command line doesn't produce an error
			if (andSign)
			{
				usrinput.erase(andSignIndex, andSignIndex + 1);
			}
		}

		if (usrinput == "exit")
		{
			exit(0);
		}



		//separates the strings into the vector
		iss.str(usrinput);
		string val;
		vector<string> commands;
		while(iss >> val)
		{
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
				string str1 = "/bin/";
				str2 = str1.append(str2);
			}
			
			cp[i] = new char[str2.length() + 1];
			strcpy(cp[i], str2.c_str());
		}
		cp[size] = new char[8];
		cp[size] = NULL;
		//checks for array values
		/*for (int i = 0; i < size; ++i)
		{
			cout << "Array at " << i << ": " << cp[i] << endl;
		}*/

		pid_t child_pid = fork();
		if (child_pid == 0)
		{
			//child process
			if (execv(cp[0], cp) == -1)
			{
				perror("EXECLV FAILED: ");
				for (int i = 0; i < size; ++i)
				{
					delete[] cp[i];
				}
				delete [] cp;
				exit(0);
			}
			for (int i = 0; i < size; ++i)
			{
				delete[] cp[i];
			}
			delete [] cp;
		}
		else
		{
			//parent process, must wait for child process to finish
			if (andSign == false)
			{
				wait(0);
			}
			for (int i = 0; i < size; ++i)
			{
				delete[] cp[i];
			}
			delete [] cp;
		}
	}
	return 0;
}
