#include <iostream>
#include "proj5.h"

using namespace std;

int main()
{
   int index;
   char quote[] = "doo";
   MyString line1("Howdy diddly doo");
   
   index = line1.Find(quote);
   cout<<index<<endl;
   
   return 0;
}
