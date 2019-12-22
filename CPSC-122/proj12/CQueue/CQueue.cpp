#include <iostream>
#include "CQueue.h"

using namespace std;

CQueue::CQueue(int size)
{
   qsize = size;
   
   q = new itemType[qsize];
   
   rear = qsize - 1;
   front = 0;
   
   num_elements = 0;
}

CQueue::~CQueue()
{
   delete q;
}
bool CQueue::IsEmpty()
{
   if(num_elements == 0)
   {
      return true;
   }
   return false;
}

bool CQueue::IsFull()
{
   if(num_elements == qsize)
   {
      return true;
   }
   return false;
}

itemType CQueue::Peek()
{
   return q[front];
}

void CQueue::Enqueue(itemType item)
{
   rear = (rear + 1) % qsize;
   q[rear] = item;
   num_elements += 1;
}

void CQueue::Dequeue()
{
   front = (front + 1) % qsize;
   num_elements -= 1;
}
