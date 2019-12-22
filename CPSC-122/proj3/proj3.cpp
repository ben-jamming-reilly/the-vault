/*
Class: CPSC122
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj3.cpp
To Build: g++ proj3.cpp
To Execute: ./a.out
*/

#include <iostream>
#include <ctype.h>

using namespace std;

int my_strcmp(char *str1, char *str2);
char *my_strcpy(char* str1, char* str2);
/*
Pre: str1 and str2 point to cstrings, ideally they contain only alphabetic characters
     but they can be technically be any ascii value
Post: by alphabetic organization; returns 1 if str1 comes before str2
                                  returns -1 if str2 comes before str1
                                  returns 0 if str1 and str2 are equivalent
*/
int my_strcmp(char *str1, char *str2)
{
   int compare = 7, i = 0;
   
   while(true)
   {   
      if(tolower(str1[i]) < tolower(str2[i]))//test for string1 < string2
      {
         compare = -1;
         break;
      }
      else if(tolower(str1[i]) > str2[i])//test for string1 > string2
      {
         compare = 1;
         break;
      }
      else if(str1[i] == '\0' && str2[i] == '\0')//test for string1 = string2
      {
         compare = 0;
         break;
      }
      i += 1;
   }
   return compare;
}
/*
pre: *str1 points to a cstring of length (n + 1)
     *str2 points to a cstring of length (n)
post: str2 has been copied into str1. A pointer to str1 is returned
*/
char *my_strcpy(char* str1, char* str2)
{
   int i = 0;
   while(str1[i] != '\0')
   {
      str1[i] = str2[i];
      i += 1;
   }
   return str1;
}





