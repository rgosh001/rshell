//working post-turn in
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
#include <wait.h>

using namespace std;

int getNumBlocks(vector<string> pipes)
{
   int blocks = 0;
   for(int i = 0; i < pipes.size(); ++i)
   {
      if(pipes.at(i) == "|")
      {
         ++blocks;
      }
   }
   return blocks + 1;
}

int main()
{
   string usrin = "";
   vector<int> pids;
   while(usrin != "exit")
   {
      bool andSign = false;
      int andSignIndex;
      int poundIndex = -1;
      //gets local machine name
      char hostname[128];
      gethostname(hostname, sizeof hostname);
      cout << getlogin() << "@" << hostname << "$ ";
      getline(cin, usrin);
      
      if(usrin == "exit")
      {
         exit(0);
      }

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

      if(poundIndex != -1)
      {
         usrin.erase(poundIndex, usrin.size());
      }

      if(andSign)
      {
         usrin.erase(andSignIndex, andSignIndex + 1);
      }
      

      istringstream iss;
      iss.str(usrin);
      vector<string> pipes;
      string val;
      while(iss >> val)
      {
         int foundOperatorIndex;
         if (val == "<" || val == ">" || val == "|" || val == ">>")
         {
            pipes.push_back(val);
         }
         else
         {
            bool foundOperator = false;
            for(int i = 0; i < val.size(); ++i)
            {
               if(val.at(i) == '<' || val.at(i) == '>' || val.at(i) == '|')
               {
                  foundOperator = true;
                  foundOperatorIndex = i;
                  break;
               }
            }
            if(foundOperator == true)
            {
               while (foundOperator == true)
               {
                  if (val == "<" || val == ">" || val == "|" || val == ">>")
                  {
                     pipes.push_back(val);
                     break;
                  }
                  else if(foundOperatorIndex > 0)
                  {
                     string wordToPush = val.substr(0, foundOperatorIndex);
                     pipes.push_back(wordToPush);
                     val.erase(0, foundOperatorIndex);
                  }
                  else if(foundOperatorIndex == 0 && val.at(foundOperatorIndex + 1) == '>')
                  {
                     string wordToPush = val.substr(foundOperatorIndex, foundOperatorIndex+2);
                     pipes.push_back(wordToPush);
                     val.erase(foundOperatorIndex, foundOperatorIndex+2);
                  }
                  else if(foundOperatorIndex == 0)
                  {
                     string wordToPush = val.substr(foundOperatorIndex, foundOperatorIndex+1);
                     pipes.push_back(wordToPush);
                     val.erase(foundOperatorIndex, foundOperatorIndex+1);
                  }
                  else
                  {
                     pipes.push_back(val);
                  }
                  for(int i = 0; i < val.size(); ++i)
                  {
                     cout << val.size() << endl;
                     if(val.at(i) == '<' || val.at(i) == '>' || val.at(i) == '|')
                     {
                        foundOperator = true;
                        foundOperatorIndex = i;
                        break;
                     }
                     else
                     {
                        pipes.push_back(val);
                        foundOperator = false;
                     }
                  }
               }
            }
            else
            {
               pipes.push_back(val);
            }
         }
      }

      string filename;

      bool leftcarrat = false;
      bool rightcarrat = false;
      bool doublecarrat = false;
      bool piping = false;

      int numBlocks = getNumBlocks(pipes);
      int carratIndex;
      int sizeforArray = 0;
      int index = 0;
      for(int i = 0; i < pipes.size(); ++i)
      {
         if(pipes.at(i) == "|")
         {
            piping = true;
         }
         if(pipes.at(i) == "<")
         {
            leftcarrat = true;
            filename = pipes.at(i+1);
            carratIndex = i;
         }
         if(pipes.at(i) == ">")
         {
            rightcarrat = true;
            filename = pipes.at(i+1);
            carratIndex = i;
         }
         if(pipes.at(i) == ">>")
         {
            doublecarrat= true;
            filename = pipes.at(i+1);
            carratIndex = i;
         }
         ++sizeforArray;
         ++index;
      }

      char **cp = new char*[sizeforArray * sizeof(char*)];

      if(leftcarrat == true)
      {
         for(int i = 0; i < carratIndex; ++i)
         {
            string str = pipes.at(i);
            if(pipes.at(i) != "<")
            {
               if(i ==0)
               {
                  string strtemp = "/bin/";
                  str = strtemp.append(str);
               }
               cp[i] = new char[str.length() + 1];
               strcpy(cp[i], str.c_str());
            }
         }
         cp[sizeforArray] = new char[8];
         cp[sizeforArray] = NULL;

      }
      
      if(piping == true && leftcarrat == false && rightcarrat == false
                                               && doublecarrat == false)
      {
         for(int i = 0; i < carratIndex; ++i)
         {
            string str = pipes.at(i);
            if(pipes.at(i) != ">")
            {
               if(i ==0)
               {
                  string strtemp = "/bin/";
                  str = strtemp.append(str);
               }
               cp[i] = new char[str.length() + 1];
               strcpy(cp[i], str.c_str());
            }
         }
         cp[sizeforArray] = new char[8];
         cp[sizeforArray] = NULL;

         close(1);
         int fd = open(filename.c_str(), O_RDWR|O_CREAT);
         if(fd == -1)
         {
            perror("Open Failed: ");
            exit(0);
         }
         dup2(fd, 1);
         execvp(cp[0], cp);
      }

      if(rightcarrat == true)
      {
         for(int i = 0; i < carratIndex; ++i)
         {
            string str = pipes.at(i);
            if(pipes.at(i) != ">")
            {
               if(i ==0)
               {
                  string strtemp = "/bin/";
                  str = strtemp.append(str);
               }
               cp[i] = new char[str.length() + 1];
               strcpy(cp[i], str.c_str());
            }
         }
         cp[sizeforArray] = new char[8];
         cp[sizeforArray] = NULL;

      }

      if(doublecarrat == true)
      {
         for(int i = 0; i < carratIndex; ++i)
         {
            string str = pipes.at(i);
            if(pipes.at(i) != ">>")
            {
               if(i ==0)
               {
                  string strtemp = "/bin/";
                  str = strtemp.append(str);
               }
               cp[i] = new char[str.length() + 1];
               strcpy(cp[i], str.c_str());
            }
         }
         cp[sizeforArray] = new char[8];
         cp[sizeforArray] = NULL;


      }
      
      //int pfd[2];
      int pid = fork();
      int status = 0;
      pids.push_back(pid);
      if(pid == 0)
      {
         if(leftcarrat == true)
         {
            int fd = open(filename.c_str(), O_RDWR);
            if(fd == -1)
            {
               perror("Open Failed: ");
               exit(0);
            }
            close(0);
            if(dup(fd) == -1)
            {
               perror("Dup Failed: ");
               exit(0);
            }
            if(execv(cp[0], cp) == -1)
            {
               perror("Execv failed: ");
               exit(0);
            }
         }
         if(rightcarrat == true)
         {
            int fd = open(filename.c_str(), O_RDWR|O_CREAT);
            if(fd == -1)
            {
               perror("Open Failed: ");
               exit(0);
            }
            close(1);
            if(dup(fd) == -1)
            {
               perror("Dup Failed: ");
               exit(0);
            }
            if(execv(cp[0], cp) == -1)
            {
               perror("Execv failed: ");
               exit(0);
            }
         }
         if(doublecarrat == true)
         {
            int fd = open(filename.c_str(), O_RDWR|O_CREAT|O_APPEND);
            if(fd == -1)
            {
               perror("Open Failed: ");
               exit(0);
            }
            close(1);
            if(dup(fd) == -1)
            {
               perror("Dup Failed: ");
               exit(0);
            }
            if(execv(cp[0], cp) == -1)
            {
               perror("Execv failed: ");
               exit(0);
            }
         }
      }
      wait(&status);
      if(status < 0)
      {
         perror("Abnormal Exit: ");
      }
      else
      {
         //do something
      }
   }
   return 0;
}
