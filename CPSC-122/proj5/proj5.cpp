/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj5.cpp
To Build: g++ proj5.cpp [test project].cpp
To Execute: ./a.out
*/
#include <cstring>
#include <iostream>
#include <ctype.h>
using namespace std;

#include "proj5.h"
/*
Pre: strIn is C-String
Post: An instance of MyString is created and set to the contents of strIn
*/ 
MyString::MyString(char const* strIn)
{
  str = new char[strlen(strIn) + 1];
  strcpy(str,strIn);
}
/*
Pre: none
Post: returns dynamically allocated memory to the heap 
*/ 
MyString::~MyString()
{
  delete [] str;
}
/*
Pre: an instance of MyString exists
Post: Contents of the instance of myString is displayed on the screen
*/ 
void MyString::MyStrDisplay()
{
  cout << str << endl;
}
/*
Pre: An instance of MyString exists
Post: Number of characters in the instance of MyString, excluding
      the null character is returned
*/
int MyString::MyStrlen()
{
   int length = 0;
   while(str[length] != '\0')
   {
      length += 1;
   }
   return length;
}
/*
Pre: an instance of MyString exists whose lengthe <= length of strIn
Post: the contents of strIn overwrites the contentw of the instance
      of MyString
*/
void MyString::MyStrcpy(char const* strIn)
{
   int index = 0;
   while(strIn[index] != '\0')
   {
      str[index] = strIn[index];
      index += 1;
   }
   str[index] = '\0';
}
/*
Pre: an instance of MyString exists
Post: Compares *this with the argument lexicograpically. Returns  
     -1 if *this would appear before *strIn
      0 if the strings are the same
      1 if *this would appear after *strIn  
*/
int MyString::MyStrcmp(char const* strIn)
{
   int i = 0, compare = 666;
   while(true)
   {   
      if(tolower(str[i]) < tolower(strIn[i]))//test for string < stringIn
      {
         compare = -1;
         break;
      }
      else if(tolower(str[i]) > tolower(strIn[i]))//test for string > stringIn
      {
         compare = 1;
         break;
      }
      else if(str[i] == '\0' && strIn[i] == '\0')//test for string = stringIn
      {
         compare = 0;
         break;
      }
      i += 1;
   }
   return compare;
}
   /*
Pre: an instance of MyString exists
Post: if strIn is a substring of the instance of MyString, returns
      its starting positon, -1 otherwise. Find is not case sensitive.
      "Str" == "sTr"
*/
int MyString::Find(char const* strIn)
{
   int str_length = 0, strIn_length = 0;
   int ch_match = 0;
   
   //gets objects string length
   str_length = this->MyStrlen();
   
   //gets substring length
   while(strIn[strIn_length] != '\0')
   {
      strIn_length += 1;
   }
   
   //Check every possible spot substring could fit
   for(int i = 0; i < (str_length - strIn_length + 1); i++)
   {
      ch_match = 0;
      //Goes through Sub-String and counts matches
      for(int j = 0; j < strIn_length; j++)
      {  
         if(tolower(str[i+j]) == tolower(strIn[j]))
         {
            ch_match += 1;
         }
      }
      //checks if both substring are identical
      if(ch_match == strIn_length)
      {
         return i;
      }
   }
   
   return -1;
}







