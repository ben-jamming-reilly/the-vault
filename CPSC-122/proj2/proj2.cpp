/*
Class: CPSC122
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj2.cpp
To Build: g++ proj2.cpp -o prime_print
To Execute: ./prime_print [file_name].txt
*/

#include <iostream>
#include <math.h>
#include <fstream>
#include <string.h>

using namespace std;

//User Input
int Get_Amount_Primes();
int Get_Amount_Columns();
//Test for Primes
bool Is_Prime(int num);
//Write to File
void Print_Primes_File(int num_primes, int num_columns, string file_name);

int main(int argc, char *argv[])
{
   int num_columns, num_primes;
   string file_name;
   
   //gets the string of the file name from command line
   file_name = argv[1];
   
   //gets user input
   num_primes = Get_Amount_Primes();
   num_columns = Get_Amount_Columns();
   
   //prints primes to file
   Print_Primes_File(num_primes, num_columns, file_name);
   
   return 0;
}


/*
pre: n/a
post: will get an integer value from the user and return it
*/
int Get_Amount_Primes()
{
   int prime_nums;
   cout<<"How many prime numbers do you want?   ";
   cin>>prime_nums;
   return prime_nums;
}
/*
pre: n/a
post: will get an integer value from the user and return it
*/
int Get_Amount_Columns()
{
   int column_nums;
   cout<<"How many columns do you want?   ";
   cin>>column_nums;
   return column_nums;
}
/*
pre: num is an natural number >= 2
post: returns true if it is prime
      returns false if it is composite
*/
bool Is_Prime(int num)
{
   bool prime = true;
   //checks if number is divisible by any
   for(int i = 2; i <= sqrt(num); i++)
   {
      if(!(num % i))
      {
         prime = false;
         break;
      }
   }
   return prime;
}
/*
pre: num_primes is the number of primes printed
     num_columns is the number of columns the primes are ordered in
     file_name is the name of the file the primes are written to
post: will write the a certain amount of prime numbers to a file ordered by
      column
*/
void Print_Primes_File(int num_primes, int num_columns, string file_name)
{
   int num = 2;
   
   ofstream fout;
   fout.open(file_name);
   
   //prints desire amount of primes  
   for(int i = 0; i < num_primes; i++)
   {
      //finds the next prime
      while(!(Is_Prime(num)))
      {
         num += 1;
      }
         
      fout<<num<<"\t";
      
      //print newline after every mutliple of columns
      if(!((i+1) % num_columns))
      {
         fout<<endl;
      }
      num += 1;
   }   
   fout.close();
}
