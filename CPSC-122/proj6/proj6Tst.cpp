/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj6.cpp
To Build: g++ proj6.cpp proj6Tst.cpp
To Execute: ./a.out
*/
#include <iostream>
#include "proj6.h"

using namespace std;

int main()
{
   List *forward;
   List *backward;
      
   forward = new List;
   backward = new List;
   
   for(int i = 0; i < 5; i++)
   {
      forward->PutItemH(i);
   }
   
   forward->Print();
   
   for(int i = 0; i < 5; i++)
   {
      backward->PutItemH(forward->GetItemH());
      forward->DeleteItemH();
   }
   
   backward->Print();
   
   for(int i = 0; i < 2; i++)
   {
      backward->DeleteItemH();
   }
   
   backward->Print();
   
   delete forward;
   delete backward;
   
   return 0;
}
