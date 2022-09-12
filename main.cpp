
//
// Author: Abdallah Mohammad, UIC, Spring 2021
//
// A project for classes to maintain, enroll and waitlist students
//


#include <iostream>
#include <string>
#include <fstream>
#include "classreg.h"
#include "pqueue.h"
#include "queue.h"

using namespace std;

//made for the waitlist function 
void wait(string student, int pri, ClassReg &myClass)
{
   if(myClass.searchEnrolled(student) >= 0)
   {
      cout << "Student '" << student << "'" << " enrolled in " << myClass.getName() << endl << endl;
      return;
   }
   myClass.waitlistStudent(student, pri);
   cout << "Student '" << student << "'" << " waitlisted for " << myClass.getName() << endl << endl;
}

//enrolled the student
void enroll(string student, ClassReg &myClass)
{
   if(myClass.searchEnrolled(student) >= 0)
   {
       cout << "Student '" << student << "'" << " enrolled in " << myClass.getName() << endl << endl;
      return;
   }
   
   if(myClass.searchWaitlisted(student) >= 0)
   {
       if(myClass.numEnrolled() < myClass.getCapacity())
       {
          int loc = myClass.searchWaitlisted(student);
          myClass.removeWaitlistedStudent(loc);
          myClass.enrollStudent(student);
          cout << "Student '" << student << "'" << " enrolled in " << myClass.getName() << endl << endl;
       }
      else
      {
         cout << "Class full, " << "'" << student << "'" << " waitlisted for " << myClass.getName() << endl << endl;
      }
      return;
   }
   try
   {
    myClass.enrollStudent(student);
      cout << "Student '" << student << "'" << " enrolled in " << myClass.getName() << endl << endl;
   }
   catch(exception e)
   {
      string lastStudent;
      int pro;
      int wait = myClass.numWaitlisted();
      if(wait == 0)
         {
            pro = 1;        
         }
      else
      {
         myClass.retrieveWaitlistedStudent(wait - 1, lastStudent, pro);
      }
      myClass.waitlistStudent(student, pro);
      cout << "Class full, " << "'" << student << "'" << " waitlisted for " << myClass.getName() << endl << endl;      
   }
   
 }

//made for the incease command
void increase(int num , string Class, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{      
   if(Class == "cs111")
            {
               if(cs111.getCapacity() > num)
               {
                  cout << "**Error, cannot decrease class capacity, ignored..."  << endl;
                  return;
               }
               cs111.setCapacity(num);
               cout << cs111.getName() << endl;
               cout << "Capacity: " << cs111.getCapacity() << endl; 
            }
            else if(Class == "cs141")
            {
               if(cs141.getCapacity() > num)
                  {
                     cout << "**Error, cannot decrease class capacity, ignored..." << endl;
                      return;
                  }
               cs141.setCapacity(num);
               cout << cs141.getName() << endl;
               cout << "Capacity: " << cs141.getCapacity() << endl;
            }
            else if(Class == "cs151")
            {
               if(cs151.getCapacity() > num)
                  {
                     cout << "**Error, cannot decrease class capacity, ignored..." << endl;
                     return;
                  }
               cs151.setCapacity(num);
               cout << cs151.getName() << endl;
               cout << "Capacity: " << cs151.getCapacity() << endl;
            }
            else if(Class == "cs211")
            {
               if(cs211.getCapacity() > num)
                  {
                     cout << "**Error, cannot decrease class capacity, ignored..." << endl;
                     return;
                  }
              cs211.setCapacity(num);
               cout << cs211.getName() << endl;
               cout << "Capacity: " << cs211.getCapacity() << endl;
            }
            else if(Class == "cs251")
            {
               if(cs251.getCapacity() > num)
                  {
                     cout << "**Error, cannot decrease class capacity, ignored..." << endl;
                     return;
                  }
              cs251.setCapacity(num);
               cout << cs251.getName() << endl;
               cout << "Capacity: " << cs251.getCapacity() << endl;
            }
            else
            {
               cout << "**Invalid class name, try again..." << endl;
            }  
}


//save the data for the following classes
void Saver(ifstream& infile, ClassReg &MyClass, string cur)
{
   MyClass.setName(cur);
         int num;
         infile >> num;
         MyClass.setCapacity(num);
         infile >> cur;
         while(cur != "#")
         {
            if(MyClass.getCapacity() == MyClass.numEnrolled())
            {
               break;
            }
            MyClass.enrollStudent(cur);
            infile >> cur;
         }
         infile >> cur;         
         int priority;
         while(cur != "#")
         {         
            infile >> priority;
            if(priority == 0)
            {
               cur = "#";               
            }
            else{
            MyClass.waitlistStudent(cur, priority);
            infile >> cur;
            }
         }
}



//used this function to see which of the classes of the following data needed to be saved in;
void FileSave(ifstream& infile, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{
   string cur;
  infile >> cur;
   while(infile)
   {
      if(cur == "cs111")
      {
         Saver(infile, cs111,  cur);
      }
      else if(cur == "cs141")
      {
         Saver(infile, cs141,  cur);
      }     
      else if(cur == "cs151")
      {
         Saver(infile, cs151,  cur);
       }      
      else if(cur == "cs211")
      {
         Saver(infile, cs211,  cur);
      }
      else if(cur == "cs251")
      {
         Saver(infile, cs251,  cur);
      }
      infile >> cur;
   }
}


//sorting the names alphabetically 
void sortAlpha(string* arr, ClassReg myClass)
{  
  for(int i = 0; i < myClass.numEnrolled(); i++)
  {
     for(int j = i + 1; j < myClass.numEnrolled(); j++)
     {
        if(arr[i] > arr[j])
        {
           string temp = arr[i];
           arr[i] = arr[j];
           arr[j] = temp;
        }
     }
  }    
}

//list function to process the list of all the classes;
void listClass(ClassReg myClass)
{
         string name;
         string* arr = new string[myClass.numEnrolled()];
         
          for(int i = 0; i < myClass.numEnrolled(); i++)
            {
               arr[i] = myClass.retrieveEnrolledStudent(i);
            }
         cout << myClass.getName() << endl;
         cout << "Capacity: " << myClass.getCapacity() << endl;
         cout << "Enrolled (" << myClass.numEnrolled() << "): ";
         sortAlpha(arr, myClass);
         for(int i = 0; i < myClass.numEnrolled(); i++)
               {
                  cout << arr[i] << " ";
               }
         cout << endl;         
        cout << "Waitlisted (" << myClass.numWaitlisted() << "): "; 
        for(int i = 0; i < myClass.numWaitlisted(); i++)
         {
            int priority = 0;   
            myClass.retrieveWaitlistedStudent(i, name, priority);
            cout << name << " (" << priority << ") "; 
         }
         cout << endl;
   
   delete[] arr;
}


//list the class the is selected
void listcmd(string Class, ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
            if(Class == "cs111")
            {
               listClass(cs111);
            }
            else if(Class == "cs141")
            {
              listClass(cs141); 
            }
            else if(Class == "cs151")
            {
              listClass(cs151); 
            }
            else if(Class == "cs211")
            {
              listClass(cs211); 
            }
            else if(Class == "cs251")
            {
              listClass(cs251); 
            }
            else
            {
               cout << "**Invalid class name, try again..." << endl;
            }
}

//lsits all the stats for the class and when changed will be updated.
void statcmd(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
         cout << cs111.getName() << ": enrolled=" << cs111.numEnrolled() << ", " << "waitlisted=" << cs111.numWaitlisted() << endl;
         cout << cs141.getName() << ": enrolled=" << cs141.numEnrolled() << ", " << "waitlisted=" << cs141.numWaitlisted() << endl;
         cout << cs151.getName() << ": enrolled=" << cs151.numEnrolled() << ", " << "waitlisted=" << cs151.numWaitlisted() << endl;
         cout << cs211.getName() << ": enrolled=" << cs211.numEnrolled() << ", " << "waitlisted=" << cs211.numWaitlisted() << endl;
         cout << cs251.getName() << ": enrolled=" << cs251.numEnrolled() << ", " << "waitlisted=" << cs251.numWaitlisted() << endl;
}

//to wait list a student in a class
void waitClass(string Class, string student, int pri, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{
   if(Class == "cs111")
         {
            wait(student, pri, cs111);
         }
         else if(Class == "cs141")
         {
            wait(student, pri, cs141);
         }
         else if(Class == "cs151")
         {
            wait(student, pri, cs151);
         }
         else if(Class == "cs211")
         {
            wait(student, pri, cs211);
         }
         else if(Class == "cs251")
         {
            wait(student, pri, cs251);
         }
         else
         {
            cout << "**Invalid class name, try again..." << endl;
         }
   
}


//to enroll the student in any class
void enrollClass(string Class, string student, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{
  if(Class == "cs111")
         {
            enroll(student, cs111);
         }
         else if(Class == "cs141")
         {
            enroll(student, cs141);
         }
         else if(Class == "cs151")
         {
            enroll(student, cs151);
         }
         else if(Class == "cs211")
         {
            enroll(student, cs211);
         }
         else if(Class == "cs251")
         {
            enroll(student, cs251);
         }
         else{
            cout << "**Invalid class name, try again..." << endl;
         } 
}

//to process the commands 
void processCommands(string Fname,istream& input, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{
  string cmd;
  input >> cmd;
   
   cout << "**Processing commands from '" << Fname << "'" << endl;
     
   while(input)
   {  
      if(cmd == "help")
      {
         cout << "stats" << endl;
         cout << "list class" << endl;
         cout << "increase class capacity" << endl;
         cout << "enroll class netid" << endl;
         cout << "waitlist class netid priority" << endl;
         cout << "process filename" << endl;
         cout << "output filename" << endl;
         cout << "quit" << endl;
      }
      else if(cmd == "q" || cmd == "quit")
      {
         cout << "**Done processing '" << Fname << "'" << endl << endl;
         return;
      }
      else if(cmd == "s" || cmd == "stats")
      {         
         statcmd(cs111, cs141, cs151, cs211, cs251);
      }
	   else if(cmd == "l" || cmd == "list")
      {
         string Class;
         input >> Class;         
         listcmd(Class, cs111, cs141, cs151, cs211, cs251);  
      }
      else if(cmd == "i" || cmd == "increase")
      {
         string Class;
         input >> Class;
         int num;
         input >> num;
         increase(num , Class, cs111, cs141, cs151, cs211, cs251);       
      }
      else if(cmd == "e" || cmd == "enroll")
      {
         string Class;
         input >> Class;
         string student;
         input >> student;
         enrollClass(Class, student, cs111, cs141, cs151, cs211, cs251);
      }
      else if(cmd == "p" || cmd == "process")
      {
         string file;
         input >> file;
     fstream my_file;   
      my_file.open(file);   
      if (!my_file.good()) // if fails to open
          {
              cout << "**Error: unable to open enrollments file " << "'" << file << "'" << endl;              
          }
         else 
         {
             processCommands(file, my_file, cs111, cs141, cs151, cs211, cs251); 
         }
      }
      else if(cmd == "w" || cmd == "waitlist")
      {
         string Class;
         input >> Class;
         string student;
         input >> student;
         int pri;
         input >> pri;
         waitClass(Class, student, pri, cs111, cs141, cs151, cs211, cs251);
      }      
      input >> cmd;
   }
}
  

//output the new file enrollments2.txt when enrolled the the new stuent;
void output(string folder, ofstream& input, ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
   input << cs111.getName() << endl;
   input << cs111.getCapacity() << endl;
   
   for(int i = 0; i < cs111.numEnrolled(); i++)
   {
      input << cs111.retrieveEnrolledStudent(i) << " ";  
   }
   input << "#\n";
   
   for(int i = 0; i < cs111.numWaitlisted(); i++)
   {
         string name;
         int priority;
         cs111.retrieveWaitlistedStudent(i, name, priority);
         input << name << " " << priority << " ";
   }
   input << "#\n";
   

   input << cs141.getName() << endl;
   input << cs141.getCapacity() << endl;
   
   for(int i = 0; i < cs141.numEnrolled(); i++)
   {
      input << cs141.retrieveEnrolledStudent(i) << " ";  
   }
   input << "#\n";
   
   for(int i = 0; i < cs141.numWaitlisted(); i++)
   {
         string name;
         int priority;
         cs141.retrieveWaitlistedStudent(i, name, priority);
         input << name << " " << priority << " ";
   }
   input << "#\n";
   
   
   
   input << cs151.getName() << endl;
   input << cs151.getCapacity() << endl;
   
   for(int i = 0; i < cs151.numEnrolled(); i++)
   {
      input << cs151.retrieveEnrolledStudent(i) << " ";  
   }
   input << "#\n";
   
   for(int i = 0; i < cs151.numWaitlisted(); i++)
   {
         string name;
         int priority;
         cs151.retrieveWaitlistedStudent(i, name, priority);
         input << name << " " << priority << " ";
   }
   input << "#\n";
   

   
   input << cs211.getName() << endl;
   input << cs211.getCapacity() << endl;
   
   for(int i = 0; i < cs211.numEnrolled(); i++)
   {
      input << cs211.retrieveEnrolledStudent(i) << " ";  
   }
   input << "#\n";
   
   for(int i = 0; i < cs211.numWaitlisted(); i++)
   {
         string name;
         int priority;
         cs211.retrieveWaitlistedStudent(i, name, priority);
         input << name << " " << priority << " ";
   }
   input << "#\n";
   
   
   input << cs251.getName() << endl;
   input << cs251.getCapacity() << endl;
   
   for(int i = 0; i < cs251.numEnrolled(); i++)
   {
      input << cs251.retrieveEnrolledStudent(i) << " ";  
   }
   input << "#\n";
   
   for(int i = 0; i < cs251.numWaitlisted(); i++)
   {
         string name;
         int priority;
         cs251.retrieveWaitlistedStudent(i, name, priority);
         input << name << " " << priority << " ";
   }
   input << "#\n";
   
   cout << "Enrollment data output to '" << folder << "'" << endl;
}

//made this function to decrease the length in the main and to loop through all the commands
void cmdLoop(string input_filename ,string cmd, ClassReg &cs111, ClassReg &cs141, ClassReg &cs151, ClassReg &cs211, ClassReg &cs251)
{
   //while loop to loop through all the commands
   while(cmd != "#")
   {
      if(cmd == "h" || cmd == "help")
      {
         cout << "stats" << endl;
         cout << "list class" << endl;
         cout << "increase class capacity" << endl;
         cout << "enroll class netid" << endl;
         cout << "waitlist class netid priority" << endl;
         cout << "process filename" << endl;
         cout << "output filename" << endl;
         cout << "quit" << endl;
      }
      else if(cmd == "q" || cmd == "quit")
      {
         cout << "**Done**" << endl;
         break;
      }
      else if(cmd == "s" || cmd == "stats")
      {         
         statcmd(cs111, cs141, cs151, cs211, cs251);
      }
	   else if(cmd == "l" || cmd == "list")
      {
         string Class;
         cin >> Class;         
         listcmd(Class, cs111, cs141, cs151, cs211, cs251);  
      }
      else if(cmd == "i" || cmd == "increase")
      {
         string Class;
         cin >> Class;
         int num;
         cin >> num;
         increase(num , Class, cs111, cs141, cs151, cs211, cs251);       
      }
      else if(cmd == "e" || cmd == "enroll")
      {
         string Class;
         cin >> Class;
         string student;
         cin >> student;
         enrollClass(Class, student, cs111, cs141, cs151, cs211, cs251);
      }
      else if(cmd == "w" || cmd == "waitlist")
      {
         string Class;
         cin >> Class;
         string student;
         cin >> student;
         int pri;
         cin >> pri;
         waitClass(Class, student, pri, cs111, cs141, cs151, cs211, cs251);
      }
      else if(cmd == "p" || cmd == "process")
      {
         string file;
         cin >> file;
     fstream my_file;   
      my_file.open(file);   
      if (!my_file.good()) // if fails to open
          {
              cout << "**Error: unable to open enrollments file " << "'" << input_filename << "'" << endl;              
          }
         else 
         {
             processCommands(file, my_file, cs111, cs141, cs151, cs211, cs251); 
         }
          
      }
      else if(cmd == "o" || cmd == "output")
      {
         ofstream info;
         string folder;
         cin >> folder;       
      info.open(folder);   
      if (!info.good()) // if fails to open
          {
              cout << "**Error: unable to open enrollments file " << "'" << input_filename << "'" << endl;              
          }
         else
         {
               output(folder, info, cs111, cs141, cs151, cs211, cs251);         
               info.close();
         }                 
      }
      else 
      {
         cout << "**Invalid command, please try again..." << endl;
      }      
   cout << "Enter a command (help for more info, quit to stop)>" << endl; 
   cin >> cmd;
   }   
}

int main(){ 
   ClassReg cs111, cs141, cs151, cs211, cs251;
   string name;
   ifstream infile;
   string input_filename;
   cout << "**CS Enrollment System**" << endl;
   cout << "Enter enrollments filename>" << endl << endl;
   cin >> input_filename;
   
   infile.open(input_filename);
    if (!infile.good()) // if fails to open
    {
        cout << "**Error: unable to open enrollments file " << "'" << input_filename << "'" << endl;
        return 0;
    }
   
    FileSave(infile,  cs111,  cs141,  cs151,  cs211, cs251);
    
   infile.close();   
   string cmd;
   
   cout << "Enter a command (help for more info, quit to stop)>" << endl;
   cin >> cmd; 
   
   cmdLoop(input_filename, cmd, cs111, cs141, cs151, cs211, cs251);
   

   return 0;  
}





