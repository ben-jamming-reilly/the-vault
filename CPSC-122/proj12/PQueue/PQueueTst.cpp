#include "PQueue.h"

#include <iostream>
using namespace std;

int main()
{
   PQueue lst;
   
   lst.Enqueue(2);
   lst.Enqueue(4);
   lst.Enqueue(6);
   
   lst.EnqueuePty(7);
   
   lst.Print();
   
   return 0;
}
