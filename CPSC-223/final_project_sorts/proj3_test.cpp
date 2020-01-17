/*
Ben Reilly 
Eric Gustin
Brian Steuber
Chris Fergueson 

Implements Stooge, Worse, Cocktail, & Ben Sort
along with a basic testing frame-work
*/

//TO RUN:
//$./sortTest   [ben]      [data.txt]
//            [cocktail]
//             [worse]
//             [stooge]

#include "proj3.h"

int main(int argc, char **argv)
{
   string file_name, sort_type;
   if(argc != 3)
   {
      cout<<"ERROR, invalid number of arguments"<<endl;
      return 1;
   }
   sort_type = argv[1];
   file_name = argv[2];
   
   if(sort_type == "stooge" || sort_type == "s")
   {
      cout<<"<...STOOGE SORT...>"<<endl;
      run_test(file_name, stooge_sort);
   }
   else if(sort_type == "worse" || sort_type == "w")
   {
      cout<<"<...WORSE SORT...>"<<endl;
      run_test(file_name, worse_sort);
   }
   else if(sort_type == "cocktail" || sort_type == "c")
   {
      cout<<"<...COCKTAIL SORT...>"<<endl;
      run_test(file_name, cocktail_sort);
   }
   else if(sort_type == "ben" || sort_type == "b")
   {
      cout<<"<...BEN SORT...>"<<endl;
      run_test(file_name, ben_sort);
   }
   else
   {
      cout<<"ERROR, invalid sort argument"<<endl;
   }
   
   return 0;
}





