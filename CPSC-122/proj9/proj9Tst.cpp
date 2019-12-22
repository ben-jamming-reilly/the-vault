#include "proj9.h"

#include <iostream>

using namespace std;

int main()
{
   List4 lst1;
   
   lst1.Insert(111,1);
   lst1.Insert(12,1);
   lst1.Insert(20,1);
   lst1.Insert(50,1);
   lst1.Insert(72,1);
   lst1.Insert(7,1);
   lst1.Insert(101,3);
   lst1.Insert(19,4);
   lst1.Insert(24,1);
   lst1.Insert(48,2);
   lst1.Insert(67,8);
   lst1.Insert(7,1);
   lst1.Insert(-111,6);
   
   lst1.PrintForward();
   
   lst1.Sort();
   
   cout<<endl;
   lst1.PrintForward();
   
   
   
   return 0;
}
