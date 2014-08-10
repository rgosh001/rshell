#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

using namespace std;

int main(int argc, char* argv[])
{

   string usrinput;
   
   bool runShell = true;
   while(runShell)
   {
      istringstream iss;

      //getting user input from the command line and will
      //stream it into a vector
      getline(cin, usrinput);

      //need to get rid of "#" for comments
      int poundIndex = false;

      //need to check for "&" for background process
      int andSignIndex;
      int andSign = false;
      for(int i = 0; i < usrinput.size(); ++i)
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
      if(poundIndex != false)
      {
         usrinput.erase(poundIndex, usrinput.size());
      }
      
      //removed "&" so that the command line doesn't produce an error
      if (andSign)
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
      char ** arr;
      arr = new char*[size * sizeof(char*)];

      //copies command and argument(s) to array
      for(int i = 0; i < size; ++i)
      {
         string str = commands.at(i);
         if(i == 0)
         {
            string str1 = "/bin/";
            str = str1.append(str);
         }
         arr[i] = new char[str.length() +1];
         strcpy(arr[i], str.c_str());
      }

      arr[size] = new char[8];
      arr[size] = NULL;


      
   }

/*   char *dirName = "ls";
   DIR *dirp;
   if (!(dirp  = opendir(dirName)))
    {
       cerr << "Error(" << errno << ") opening " << dirName << endl;
       return errno;
   }
   dirent *direntp;
   while ((direntp = readdir(dirp)))
       cout << direntp->d_name << endl;  // use stat here to find attributes of file
   closedir(dirp);*/
}

