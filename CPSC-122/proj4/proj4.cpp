/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj4.cpp
To Build: g++ proj4.cpp
To Execute: ./a.out names.in 200 [output file name].txt
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;

void File_To_List(char *file_name,char *list[], int num_lines);
void List_To_File(char *file_name, char *list[], int num_lines);
int my_strcmp(char *str1, char *str2);

//Sourced from ex19.cpp
void sort(char **, int);
int find_smallest(char**,int,int);
void swap(char **,int,int);

int main(int argc, char *argv[])
{
   int num_lines = atoi(argv[2]);
   int length;
   
   char *file_in = argv[1];
   char *file_out = argv[3];
   char **list = new char*[num_lines];
   
   File_To_List(file_in, list, num_lines);
   
   sort(list, num_lines); 
   
   List_To_File(file_out, list, num_lines);
   
   return 0;
}
/*
Pre: *file_name is a cstring that is the name of a file that has list of names
     *list[] is an array of pointers
     num_lines is the size of that array
Post: *list[] will be filled with the names from that file
*/
void File_To_List(char *file_name,char **list, int num_lines)
{
   int length;
   char line[80];
   
   ifstream fin;
   fin.open(file_name);
   
   for(int i = 0; i < num_lines; i++)
   {
      fin.getline(line, 80, '\n');
      length = strlen(line) + 1;
      list[i] = new char [length];
      strcpy(list[i], line);
   }
   fin.close();
}
/*
Pre: *file_name is a cstring with the name of a file
     *list[] is an array of pointers to cstrings
     num_lines is the size of that array
Post: writes *list[] line by line to the file
*/
void List_To_File(char *file_name, char *list[], int num_lines)
{
   ofstream fout;
   fout.open(file_name);
   for(int i = 0; i < num_lines; i++)
   {
      fout<<list[i];
      if(i < num_lines -1)
      {
         fout<<endl;
      }
   }
   fout.close();
}
/*
Pre: str1 and str2 point to cstrings, ideally they contain only alphabetic characters
     but they can be techniquely be any ascii value
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
      else if(tolower(str1[i]) > tolower(str2[i]))//test for string1 > string2
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

//Sourced from example ex19.cpp

/*
Pre: **stuff is an array of pointers to cstrings
     size is the size of that array
Post: **stuff will be alphabetically sorted
*/
void sort(char **stuff, int size)
{
   for (int cur = 0; cur < size - 1; cur++) //bc next-to-last item is compared with the last
   {
      int smallest = find_smallest(stuff, cur, size);  //return index of smallest item
      swap(stuff, smallest, cur);  //swap the smallest item with the current item
   }
}
/*
Pre: **stuff is an array of pointers to cstrings
     start is the lower limit where the algorith will search from
     size is the size of the array 
Post: will return the index of the smallest element of the array from the starting
      index to the end of the array
*/
int find_smallest(char **stuff, int start, int size)
{
   int idxSmall = start;
   
   for(int i = start + 1; i < size; i++)
   {
      if(my_strcmp(stuff[i], stuff[idxSmall]) < 0)
      {
         idxSmall = i;
      }
   }
   return idxSmall;
}
/*
Pre: **stuff is an array of pointers to cstrings
     a >= 0
     b < size of array
Post: swaps the elements at index a and index b with eachother
*/
void swap(char **stuff, int a, int b)
{
   char *spare;
   spare = stuff[a];
   stuff[a] = stuff[b];
   stuff[b] = spare;
}
