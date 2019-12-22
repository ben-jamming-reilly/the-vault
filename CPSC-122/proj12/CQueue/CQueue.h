/*
Class: CPSC 122-01
Ben Reiily & Dillon Shipley
GU Username: breilly4 / dshipley
Submitted By: Ben Reilly
File Name: proj12.h
To Build: g++ PQueueTst.cpp PQueue.cpp queue2.cpp list2.cpp 
To Execute: ./a.out
*/

#ifndef CQUEUE_H
#define CQUEUE_H

typedef int itemType;

class CQueue
{
   public:
      /*
      Post: A new circular queue of size int size is created
      */
      CQueue(int size);
      /*
      Pre: A circular queue exists
      Post: The circular queue has been deleted
      */
      ~CQueue();
      /*
      Pre: A circular queue exists with an uncertain number of objects
      Post: Returns true if there are no objects in the queue
      */
      bool IsEmpty();
      /*
      Pre: A circular queue exists with an uncertain number of objects
      Post: Returns true if the queue is full
      */
      bool IsFull();
      /*
      Pre: A queue exists with at least one element
      Post: Returns the next element to be dequeued
      */
      itemType Peek();
      /*
      Pre: A queue exists
      Post: Places an element in the queue
      */
      void Enqueue(itemType item);
      /*
      Pre: A circular queue exists with at least one object
      Post: Takes out the first element put in
      */
      void Dequeue();
   private:
      itemType* q;
      int front;
      int rear;
      int qsize;
      int num_elements;
};
#endif
