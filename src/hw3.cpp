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
               if(val.at(i) == '<' || val.at(i) == '>' || val.at(i) == '|' || val.at(i) == ">>")
               {
                  foundOperator = true;
                  foundOperatorIndex = i;
                  break;
               }
            }
            if(foundOperator)
            {
               if(foundOperatorIndex > 0)
               {
                  string wordToPush = val.substr(0, foundOperatorIndex);
                  pipes.push_back(wordToPush);
                  val.erase(0, foundOperatorIndex);
               }
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

/*
               if(foundOperatorIndex == 0 && val.at(foundOperatorIndex) == '>'
                                          && val.at(foundOperatorIndex + 1) == '>')
               {
                  pipes.push_back(">>");
                  val.erase(foundOperatorIndex, foundOperatorIndex + 1);
               }
               else if(foundOperatorIndex == val.size() - 1 && val.at(foundOperatorIndex) == '>'
                                                        val.at(foundOperatorIndex + 1) == '>')
               {
                  pipes.push_back(">>");
                  val.erase(val.size()-1, val.size());
               }
               else if(foundOperatorIndex + 1 == '>' )
               {

               }
*/
