/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj7Tst.cpp
To Build: g++ proj7.cpp proj7Tst.cpp
To Execute: ./a.out
*/
#include <iostream>
#include "proj7.h"

using namespace std;

int main()
{
   List2 *bucketPtr = new List2;
   
   for(int i = 0; i < 5; i++)
   {
      bucketPtr->PutItemT(i);
   }
   bucketPtr->Print();
   
   
   bucketPtr->DeleteItemH();
   bucketPtr->DeleteItemT();
   
   bucketPtr->Print();
   
   List2 bucket(bucketPtr);
   
   bucket.PutItemT(4);
   bucket.PutItemT(5);
   
   bucket.Print();
   
   delete bucketPtr;
   bucketPtr = NULL;
   
   return 0;
}
