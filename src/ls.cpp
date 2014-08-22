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
bool isFile(const char* target)
{
   struct stat statbuf;
   stat(target, &statbuf);
   return S_ISREG(statbuf.st_mode);
}

bool isDirectory(char const * path)
{
   struct stat s;
   stat(path, &s);
   return S_ISDIR(s.st_mode);
}

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
   string combinedArg = "";
   int t = 0;
   while(!arguments.empty())
   {
      string temp = arguments.back();
      temp.erase(0, 1);
      combinedArg.append(temp);
      arguments.pop_back();
   }

   bool a = false;
   bool l = false;
   bool R = false;
   for(int i = 0; i < combinedArg.size(); ++i)
   {
      if(combinedArg.at(i) == 'l')
      {
         l = true;
      }
      if(combinedArg.at(i) == 'a')
      {
         a = true;
      }
      if(combinedArg.at(i) == 'R')
      {
         R = true;
      }
   }

   struct stat s;
   vector<string> files;
   while(!directory.empty())
   {
      string currentDirectory = directory.back();
      if(stat(currentDirectory.c_str(), &s) == -1)
      {
         perror("Stat Error: ");
         exit(0);
      }

      //for file input eg()
      if(directory.size() == 1 && isFile(currentDirectory.c_str()))
      {
         struct stat t;
         if (stat(currentDirectory.c_str(), &t) == -1){
            perror("Stat Error: ");
            exit(0);
         }
         //ERROR CHECK for the two structs below are done when they are called.
         //See line 161 & 172
         struct passwd *pwd;
         struct group *grp;
         if(l == true){
            if (t.st_mode & S_IFDIR){
               cout << 'd';
            }else if(t.st_mode & S_IFLNK){
               cout << 'l';
            }else{
               cout << '-';
            }

            if (t.st_mode & S_IRUSR){
               cout << 'r';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IWUSR){
               cout << 'w';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IXUSR){
               cout << 'x';
            } else{
               cout << '-';
            }

            if (t.st_mode & S_IRGRP){
               cout << 'r';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IWGRP){
               cout << 'w';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IXGRP){
               cout << 'x';
            } else{
               cout << '-';
            }

            if (t.st_mode & S_IROTH){
               cout << 'r';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IWOTH){
               cout << 'w';
            } else{
               cout << '-';
            }
            if (t.st_mode & S_IXOTH){
               cout << 'x';
            } else{
               cout << '-';
            }
            cout << " ";
            
            //stdout # of links
            cout << t.st_nlink << " ";

            //stdout usrname
            if ((pwd = getpwuid(t.st_uid)) != NULL)
            {
               cout << pwd->pw_name << " ";
            }
            else
            {
               cerr << "ERROR: " << errno << endl;
               exit(0);
            }
            
            //stdout groupname
            if ((grp = getgrgid(t.st_gid)) != NULL)
            {
               cout << grp->gr_name << " ";
            }
            else
            {
               cerr << "ERROR: " << errno << endl;
               exit(0);
            }

            //stdout filesize
            cout << s.st_size << " ";

            //stdout the time
            char buff[20];
            struct tm * timeinfo;
            timeinfo = localtime (&(t.st_mtime));
            if(strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo) == 0)
            {
               perror("Time Error: ");
            }
            cout << buff << " ";
         }

         //stdout the name of the file
         if (l == false)
         {
            cout << currentDirectory.erase(0, 2)<< " ";
         }
         else
         {
            cout << currentDirectory << " ";
         }
         cout << endl;
         break;
      }
      /*if (currentDirectory == ".")
      {
         cout << "./: " << endl;
      }*/
      else
         cout << currentDirectory << ": " << endl;
      char const *dirName = directory.back().c_str();
      DIR *dirp;
      if (!(dirp  = opendir(dirName)))
       {
          cerr << "Error(" << errno << ") opening " << dirName << endl;
          perror("Error is: ");
          exit(0);
      }
      dirent *direntp;
      while ((direntp = readdir(dirp)))
      {
         string fullPath = currentDirectory;
         fullPath.append("/");
         string fileName = direntp->d_name;
         fullPath.append(fileName);

         if(direntp->d_name[0] == '.' && a == false)
         {
            continue;
         }

         struct stat buf;
         if(stat(fullPath.c_str(), &buf) == -1)
         {
            perror("Stat Error: ");
            exit(0);
         }
         //Error check for two structs below are done during their calls below.
         //See line 314 & 325
         struct passwd *pwd;
         struct group *grp;

         if (R)
         {
            if (buf.st_mode & S_IFDIR){
            directory.push_back(fullPath);
            }
         }

         if(l == true){

            if (buf.st_mode & S_IFDIR){
               cout << 'd';
            }else if(buf.st_mode & S_IFLNK){
               cout << 'l';
            }else{
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
            if(strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo) == 0)
            {
               perror("Time Error: ");
            }
            cout << buff << " ";
         }
         //stdout the name of the file
         if (l == false)
         {
            cout << direntp->d_name << " ";
         }
         else
         {
            cout << direntp->d_name << endl;
         }
      }
      closedir(dirp);
      directory.pop_back();
      cout << endl << endl;
      if (directory.size() == 1)
      {
         return;
      }
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
   
   vector<string> arguments;
   vector<string> directory;
   //gets directories
   for (int i = 1; i < args.size(); ++i)
   {
      if (args.at(i).at(0) != '-')
      {
         //string path = "./";
         string st1 = args.at(i);
         //st1.insert(0,path);
         directory.push_back(st1);
      }
   }
   //get arguments
   for (int i = 1; i < args.size(); ++i)
   {
      if (args.at(i).at(0) == '-')
      {
         string temp = args.at(i);
         arguments.push_back(temp);
      }
   }

   //if there are no directories, go into current directory
   if(directory.size() == 0)
   {
      directory.push_back(".");
      //print(directory, arguments);
      //exit (0);
   }

   //checks input of directory and arguments vector
   /*for(int i = 0; i < directory.size(); ++i)
   {
      cout << directory.at(i) << endl;
   }
   for(int i = 0; i < arguments.size(); ++i)
   {
      cout << "arguments: " << arguments.at(i) << endl;
   }*/

   //runs the print function to display all directoryies and flags passed in
   print(directory, arguments);

   return 0;
}
