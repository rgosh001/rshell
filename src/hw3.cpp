#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <vector>


using namespace std;

int main()
{
   while(1)
   {
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
      
      if(pipe.at(0) != "cat")
      {
         cout << "Error: No input file argument." << endl;
         exit(0);
      }

     int fd[2];
     if(pipe(fd) == -1)
     {
        perror("Pipe Failed:");
        exit(1);
     }

     int pid = fork();
     if(pid == 0)
     {

     }

   }
   return 0;
}
