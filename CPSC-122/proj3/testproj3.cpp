#include <iostream>
#include "proj3.cpp"

int main(int argc, char *argv[])
{
   char *str1 = argv[1];
   char *str2 = argv[2];
   char *sort1;
   char *sort2;
   
   if(my_strcmp(str1, str2) == 1)
   {
      sort2 = str1;
      sort1 = str2;
   }
   else
   {
      sort1 = str1;
      sort2 = str2;
   }
   cout<<sort1<<" ~ "<<sort2<<endl;
   return 0;
}

