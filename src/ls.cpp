#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

using namespace std;

void clearVector(vector<string>&temp)
{
   while(!temp.empty())
   {
      temp.pop_back();
   }
}

bool checkArg(vector<string>arguments, string flag)
{
   for(int i = 0; i < arguments.size(); ++i)
   {
      if (arguments.at(i) == flag)
      {
         return true;
      }
   }
   return false;
}
void print(vector<string>directory, vector<string>arguments)
{
   bool l = checkArg(arguments, "-l");
   bool a = checkArg(arguments, "-a");
   bool R = checkArg(arguments, "-R");

   struct stat s;
   vector<string> files;
   while(!directory.empty())
   {
      stat(directory.back().c_str(), &s);

      char const *dirName = directory.back().c_str();
      DIR *dirp;
      if (!(dirp  = opendir(dirName)))
       {
          cerr << "Error(" << errno << ") opening " << dirName << endl;
          cout << errno;
          exit(0);
      }
      dirent *direntp;
      while ((direntp = readdir(dirp)))
      {
         if(direntp->d_name[0] == '.' && a == false)
         {
            continue;
         }
         struct stat buf;
         stat(direntp->d_name, &buf);
         struct passwd *pwd;
         struct group *grp;
         if (buf.st_mode & S_IFDIR){
            cout << 'd';
         } else{
            cout << '-';
         }

         if (buf.st_mode & S_IRUSR){
            cout << 'r';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IWUSR){
            cout << 'w';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IXUSR){
            cout << 'x';
         } else{
            cout << '-';
         }

         if (buf.st_mode & S_IRGRP){
            cout << 'r';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IWGRP){
            cout << 'w';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IXGRP){
            cout << 'x';
         } else{
            cout << '-';
         }

         if (buf.st_mode & S_IROTH){
            cout << 'r';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IWOTH){
            cout << 'w';
         } else{
            cout << '-';
         }
         if (buf.st_mode & S_IXOTH){
            cout << 'x';
         } else{
            cout << '-';
         }
         cout << " ";
         
         //stdout # of links
         cout << buf.st_nlink << " ";

         //stdout usrname
         if ((pwd = getpwuid(buf.st_uid)) != NULL)
         {
            cout << pwd->pw_name << " ";
         }
         else
         {
            cerr << "ERROR: " << errno << endl;
            exit(0);
         }
         
         //stdout groupname
         if ((grp = getgrgid(buf.st_gid)) != NULL)
         {
            cout << grp->gr_name << " ";
         }
         else
         {
            cerr << "ERROR: " << errno << endl;
            exit(0);
         }

         //stdout filesize
         cout << buf.st_size << " ";

         //stdout the time
         char buff[20];
         struct tm * timeinfo;
         timeinfo = localtime (&(buf.st_mtime));
         strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
         cout << buff << " ";

         //stdout the name of the file
         cout << direntp->d_name << endl;
         files.push_back(direntp->d_name);
      }
      closedir(dirp);
      
      directory.pop_back();
      cout << endl;
   }
}

int main(int argc, char* argv[])
{
   //put all argv[] into a vector of strings
   vector<string> args;
   for (int i = 0; i < argc; ++i)
   {
      args.push_back(argv[i]);
   }
   
   //check for exit command
   if (args.at(0) == "exit")
   {
      exit(0);
   }

   //separates the strings into the vector
   vector<string> arguments;
   vector<string> directory;
   bool matchDirectoryArguments = true;
   int argsSize = args.size();
   int argsIndex = 1;
   while(matchDirectoryArguments)
   {
      if(argsSize == 0)
      {
         break;
      }
      for (int i = argsIndex; i < args.size(); ++i)
      {
         string temp = args.at(i);
         if (temp.at(0) == '-')
         {
            arguments.push_back(temp);
            --argsSize;
         }
         else
         {
            argsIndex = i;
            break;
         }
      }
      if(directory.size() == 0)
      {
         directory.push_back(".");
      }
      
      cout << "\t-----FILE OUTPUT AREA-----\t" << endl;
      print(directory, arguments);
      clearVector(directory);
      clearVector(arguments);
      //break;
   }
   
   return 0;
}

      /*
      if(temp.at(0) == '-' && i != 0)
      {
         arguments.push_back(temp);
      }
      else if (temp.at(0) != '-' && i != 0)
      {
         directory.push_back(temp);
      }*/

   /*
      for (int i = 0; i < arguments.size(); ++i)
      {
         cout << "Argument " << i << ": " << arguments.at(i) << endl;
      }
      for (int i = 0; i < directory.size(); ++i)
      {
         cout << "Directory " << i << ": " << directory.at(i) << endl;
      
   */
