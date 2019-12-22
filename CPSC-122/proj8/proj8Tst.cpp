#include "proj8.h"
#include <iostream>

using namespace std;

int main()
{
   List3 *lst1 = new List3();
   
   lst1->PutItem(1, 10);
   lst1->PutItem(1, 20);
   lst1->PutItem(1, 30);
   lst1->PutItem(1, 40);
   lst1->PutItem(1, 50);
   
   List3 lst2(lst1);
   
   lst2.DeleteItem(4);
   lst2.PutItem(2,100);
   
   lst2.Print();
   
   
   
   return 0;
}
