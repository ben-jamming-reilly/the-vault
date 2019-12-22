/*
Class: CPSC 122-01
Ben Reiily & Dillon Shipley
GU Username: breilly4 / dshipley
Submitted By: Ben Reilly
File Name: proj12.h
To Build: g++ PQueueTst.cpp PQueue.cpp queue2.cpp list2.cpp 
To Execute: ./a.out
*/


#ifndef PQUEUE_H
#define PQUEUE_H

#include "queue2.h"

class PQueue : public Queue2
{
   public:
      PQueue();
      /*
      Pre:  None
      Post: Queue has another entry based on prioty 
      */
      void EnqueuePty(itemType item);
      
};

#endif


//Ask DePalma about this
#ifndef NULL
#define NULL 0
#endif

