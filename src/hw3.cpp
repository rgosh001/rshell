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
      if(pipes.at(pipes.size()-1) == "&")
      {
         wait = true;
      }

      int sizeOfArr = 1;
      for(int i = 0; i < pipes.size(); ++i)
      {
         if(pipes.at(i) == "|")
         {
            ++sizeOfArr;
         }
         cout << "User Input at " <<  i << ": " << pipes.at(i) << endl;
      }
      cout << "Size of Array: " << sizeOfArr << endl;
      int indexHolder = 0;
      int temp = 0;
      int count = 0;
      int pfd[2];
      vector<int> pidList;
      //while(count < sizeOfArr)
      //{
         cout << "nigga" << endl;
         if(temp != 0 && indexHolder != 0)
         {
            ++temp;
            ++indexHolder;
         }

         int size = 0;
         for(int i = temp; i < pipes.size(); ++i)
         {
            if(pipes.at(i) == "|")
            {
               break;
            }
            ++size;
            ++temp;
         }
         cout << size << " " << temp << endl;

         int zero = 0;
         cout << "hey" << endl;
         char ** cp = new char*[size * sizeof(char*)];
         for(int i = indexHolder; i < pipes.size(); ++i)
         {
            string str = pipes.at(i);
            cout << "holla" << endl;
            if(zero == 0)
            {
               cout << "here" << endl;
               string str2 = "/bin/";
               str = str2.append(str);
               ++zero;
            }
            if(pipes.at(i) == "|")
            {
               break;
            }
            
            cp[i] = new char[str.length() + 1];
            strcpy(cp[i], str.c_str());
            ++indexHolder;
         }
         cp[size] = new char[8];
         cp[size] = NULL;

         for(int i = 0; i < size; ++i)
         {
            cout << "Array at " << i << ": " << cp[i] << endl;
         }
         
         int pid = fork();
         pidList.push_back(pid);
         
         if(pid == 0)
         {
            //FIRST && input redirection
            if(count == 0)
            {
               cout << "194" << endl;
               int fd = open(cp[0], O_RDONLY|O_CREAT);
               close(0);
               dup(fd);
            }

            execv("/bin/cat", "/bin/cat");
         }
         else
         {
            cout << "Here" << endl;
         }
         ++count;
      //}
      
         
   }
   return 0;
}
