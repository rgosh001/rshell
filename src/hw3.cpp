#include <iostream>
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
      vector<string> commands;
      vector<string> names;
      string val;
      while(iss >> val)
      {
         if(val == "" || val == " ")
         {
            continue;
         }
         if(val == ">>")
         {
            commands.push_back(val);
            continue;
         }
         for(int i = 0; i < val.size(); ++i)
         {
            if(val.at(i) == '<' || val.at(i) == '|' || val.at(i) == '>')
            {
               if(val.size() > 1 && (val.at(i) == '>' && val.at(i+1) == '>' && val != ""))
               {
                  cout << "line 50" << endl;
                  if(val == ">>")
                  {
                     commands.push_back(val);
                  }
                  else
                  {
                     string front = val.substr(0,i);
                     if(front != "")
                     {
                        names.push_back(front);
                     }

                     string command = val.substr(i,2);
                     commands.push_back(command);

                     val.erase(0,i+2);
                  }
               }
               else if(val.size() > 1)
               {
                  string front = val.substr(0,i);
                  if(front != ""){
                     names.push_back(front);
                  }

                  string command = val.substr(i,1);
                  commands.push_back(command);

                  val.erase(0,i+1);
               }
         //      commands.push_back(val);
               continue;
            }
         }
         if(val != "<" && val != "|" && val != ">" && val != "")
         {
            names.push_back(val);
         }
         else if(val != "")
         {
            commands.push_back(val);
         }
      }
      for(int i = 0; i < names.size(); ++i)
      {
         cout << "Name: "<< names.at(i) << endl;
         if(i < commands.size())
         {
            cout << "Command: "<< commands.at(i) << endl;
         }
      }
      if(commands.size() != names.size()-1)
      {
         cerr << "Invalid Amount of Arguments; Will Terminate Program Now" << endl;
         exit(0);
      }
   }
   return 0;
}
