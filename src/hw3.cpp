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
      vector<string> pipes;
      string val;
      while(iss >> val)
      {
         bool foundOperator = false;
         if (val == "<" || val == ">" || val == "|" || val == ">>")
         {
            pipes.push_back(val);
         }
         else
         {
            for(int i = 0; i < val.size(); ++i)
            {
               if(val == "<" || val == ">" || val == "|" || val == ">>")
               {
                  foundOperator = true;
               }
            }
            if(foundOperator)
            {

            }
            else
            {
               pipes.push_back(vals);
            }
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
   }
   return 0;
}
