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
#include <wait.h>

using namespace std;

int handler = 0;
int stop = 0;

void sig_handler(int signum)
{
   ++handler;
   flush(cout);
}

void sig_stop(int signum)
{
   ++stop;
   cout << "S" << endl;
   
   pid_t pid = getpid();
   kill(pid, SIGSTOP);
}

char* getPath(vector<string> commands)
{
   char *cwd = new char[1024];
   char *returncwd = new char[1024];
   int lastslash = 0;

   if(getcwd(cwd, 1024) == 0)
   {
      perror("getcwd() error");
   }
   if(commands.size() == 1 && commands.at(0) == "cd")
   {
      //path char array made into string for parsing reasons
      returncwd = getenv("HOME");
      delete [] cwd;
      return returncwd;
   }
   else if(commands.size() == 2 && commands.at(0) == "cd" && commands.at(1) == ".")
   {
      //path char array made into string for parsing reasons
      delete [] returncwd;
      return cwd;
   }
   else if(commands.size() > 1 && commands.at(1) == "..")
   {
      for(int i = 0; cwd[i] != '\0'; ++i)
      {
         if(cwd[i] == '/')
         {
            lastslash = i;
         }
      }
      cout << cwd << endl;

      for(int i = 0; i < lastslash; ++i)
      {
         returncwd[i] = cwd[i];
      }
      delete [] cwd;
      return returncwd;
   }
   else if(commands.size() > 1)
   {
      string append_path = commands.at(1);
      char temp[append_path.size()+1];
      temp[append_path.size()] = 0;
      memcpy(temp, append_path.c_str(), append_path.size());

      strcpy(returncwd, cwd);
      strcpy(returncwd, temp);
      delete [] cwd;
      return returncwd;
   }

   return returncwd;
}

int main()
{
   string usrin = "";
   int exitcount = 100;
   while(usrin != "exit")
   {
      ++exitcount;
      signal(SIGINT, sig_handler);
      signal(SIGTSTP, sig_stop);
      //gets local machine name
      char hostname[128];
      gethostname(hostname, sizeof hostname);
      cout << getlogin() << "@" << hostname << "$ ";
      getline(cin, usrin);

      //path char array made into string for parsing reasons
      string strpath(getenv("PATH"));
      //cout << strpath << endl;
      
      vector<string> paths;
      string temp = "";
      for(int i = 0; i < strpath.size(); ++i)
      {
         if(strpath.at(i) == ':' || i == strpath.size()-1)
         {
            if(i == strpath.size()-1)
            {
               temp += strpath.at(i);
            }
            string slash = "/";
            temp = temp.append(slash);
            paths.push_back(temp);
            temp = "";
         }
         else
         {
            temp += strpath.at(i);
         }
      }
      
      /*for(int i = 0; i < paths.size(); ++i)
      {
         cout << paths.at(i) << endl;
      }*/
      
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
         if(commands.at(0) == "cd")
         {
            char *path = new char[1024];
            path = getPath(commands);
            cout << path << endl;
            if(chdir(path) == -1)
            {
               perror("cd failed");
            }
         }
         else
         {
            //allocating memory for the array
            int size = commands.size();
            char** cp;
            cp = new char*[size * sizeof(char*)];
            int pathindex = 0;
            while(paths.size() != 0)
            {
               //copies command and argument(s) to array for EXECV()
               for (int i = 0; i < size; ++i)
               {
                  string str = commands.at(i);
                  if (i == 0)
                  {
                     string str1 = paths.at(0);
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
                  //ONLY want to call this is it fails ALL PATHS given 
                  if(paths.size() == 1)
                     perror("Command Failed");
               }
               paths.erase(paths.begin());
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
