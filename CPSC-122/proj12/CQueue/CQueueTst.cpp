#include <iostream>
#include "CQueue.h"

using namespace std;

int main()
{
   int index = 1;
   CQueue tst(10);
   
   while(!tst.IsFull())
   {
      tst.Enqueue(index);
      index += 1;
   }
   
   tst.Dequeue();
   tst.Dequeue();
   tst.Dequeue();
   
   tst.Enqueue(12);
   tst.Enqueue(43);
   
   while(!tst.IsEmpty())
   {
      cout<<tst.Peek()<<endl;
      tst.Dequeue();
   }
   
   return 0;
}
