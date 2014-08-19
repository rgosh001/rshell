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


using namespace std;

int main()
{
   while(1)
   {
      bool wait = false;
      string usrin;
      cout << "$ ";
      getline(cin, usrin);
      
      if(usrin == "exit")
      {
         exit(0);
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
      for(int i = 0; i < pipes.size(); ++i)
      {
         cout << "User Input at " <<  i << ": " << pipes.at(i) << endl;
      }

      if(pipes.at(pipes.size()-1) == "&")
      {
         wait = true;
      }

      if(pipes.at(0) != "cat")
      {
         cout << "Error: No input file argument." << endl;
         exit(0);
      }

      //will get the size for everything up till the next |
      int size = 0;
      for(int i = 0; i < pipes.size(); ++i)
      {
         if(pipes.at(i) == "|") 
         {
            break;
         }
         else
         {
            ++size;
         }
      }
      
      cout << size << endl;

      //copy vector up untill the | occurance into array.
      char** cp;
      cp = new char*[size * sizeof(char*)];
      for(int i = 0; i < size; ++i)
      {
         if(pipes.at(i) != "|")
         {
            string tempStr = pipes.at(i);
            cp[i] = new char[tempStr.length() + 1];
            strcpy(cp[i], tempStr.c_str());
         }
      }

      int toDel = size;
      while(toDel != 0)
      {
         pipes.erase(pipes.begin());
         --toDel;
      }

      cp[size] = new char[8];
      cp[size] = NULL;

      for(int i = 0; i < size; ++i)
      {
         cout << "Array at " << i << ": ";
         cout << cp[i] << endl;
      }

      int fd = open(cp[0], O_RDWR|O_CREAT);

      /*int fd2[2];
      if(pipe(fd2) == -1)
      {
        perror("Pipe Failed:");
        exit(1);
      }

      pid_t pid  = fork();
      while(1)
      {
         if(pid == 0)
         {
            string test;
            cin >> test;




            else if (pipes.at(0) == '>')
            {
               close(0);
               pipes.erase(pipes.begin());
               int fd = open(pipes.at(0).c_str, );
            }*/
            //write to the pipe
            //write(fd[1]), "test",5);
            //dup(fd[1]);
           // cout << "test" << endl;
           // if(pipes.size() == 0)
           // {
           //    exit(0);
           // }
   }
   return 0;
}

      /*else
      {
         //wait(0);
         char buf[BUFSIZ];
         read(fd[0], bf, BUFSIZE);
         //cout << "buf = " << buf << endl;
         //read from the pipe
      }*/
