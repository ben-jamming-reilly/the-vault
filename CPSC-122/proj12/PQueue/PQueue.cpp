#include "PQueue.h"
#include <iostream>

using namespace std;

PQueue::PQueue()
{
}

void PQueue::EnqueuePty(itemType item)
{
   node *cur;
   node *nextCur;
   node *add;
   
   if(IsEmpty())
   {
      Enqueue(item);
   }
   else
   {
      nextCur = head;
      while(nextCur != NULL && nextCur->item <= item)
      {
         cur = nextCur;
         nextCur = nextCur->next;
      }
      
      if(nextCur == NULL)
      {
         Enqueue(item);
      }
      else
      {
         add = new node;
         add->item = item;
         
         add->next = nextCur;
         cur->next = add; 
      }
      
   }
}
