#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <vector>
#include <errno.h>
#include <signal.h>
//#include <wait.h>

using namespace std;

int main()
{
   string usrin = "";
   int exitcount = 100;
   while(usrin != "exit")
   {
      ++exitcount;
      //gets local machine name
      char hostname[128];
      gethostname(hostname, sizeof hostname);
      cout << getlogin() << "@" << hostname << "$ ";
      getline(cin, usrin);

      if(usrin == "exit")
      {
         if(exitcount == 0)
         {
            exit(0);
         }
         else
         {
            while(exitcount != 0)
            {
               exit(0);
               --exitcount;
            }
         }
      }

      //bool for usrin check for comments (#) and for background process (&)
      bool andSign = false;
      int andSignIndex;
      int poundIndex = -1;
      for(int i = 0; i < usrin.size(); ++i)
      {
         if(usrin.at(i) == '#')
         {
            poundIndex = i;
            break;
         }
         if(usrin.at(i) == '&')
         {
            andSign = true;
            andSignIndex = i;
            break;
         }
      }

      //erases # and comments
      if(poundIndex != -1)
      {
         usrin.erase(poundIndex, usrin.size());
      }

      //erases & if present
      if(andSign)
      {
         usrin.erase(andSignIndex, andSignIndex + 1);
      }
      
		//separates the strings into the vector
		istringstream iss;
		iss.str(usrin);
		string val;
		vector<string> commands;
		while(iss >> val)
      {
         commands.push_back(val);
      }


      int child = fork();
		if (child == 0)
		{
         if(commands.at(0) == "exit")
         {
            while(exitcount != 0)
            {
               exit(0);
               --exitcount;
            }
         }
         else if(commands.size() == 0)
         {
            continue;
         }
         else
         {
            //allocating memory for the array
            int size = commands.size();
            char** cp;
            cp = new char*[size * sizeof(char*)];
            int pathindex = 0;
            //copies command and argument(s) to array for EXECV()
            for (int i = 0; i < size; ++i)
            {
               string str = commands.at(i);
               if (i == 0)
               {
                  string str1 = "/bin/";
                  str = str1.append(str);
               }
               cp[i] = new char[str.length() + 1];
               strcpy(cp[i], str.c_str());
            }
            cp[size] = new char[8];
            cp[size] = NULL;

            //checks for array values
            /*for (int i = 0; i < size; ++i)
            {
               cout << "Array at " << i << ": " << cp[i] << endl;
            }*/

            if (execv(cp[0], cp) == -1)
            {
               perror("execv failed");
            }
         }
		}
		else
		{
			//parent process, must wait for child process to finish
			if (andSign == false)
			{
				wait(0);
			}
			/*for (int i = 0; i < size; ++i)
			{
				delete[] cp[i];
			}
			delete [] cp;*/
		}
   }
   return 0;
}
