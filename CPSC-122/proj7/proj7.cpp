/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj7.cpp
To Build: g++ proj7.cpp proj7Tst.cpp
To Execute: ./a.out
*/
#include <iostream>
#include "proj7.h"

using namespace std;

List2::List2()
{
   head = NULL;
   tail = NULL;
   length = 0;  
}

List2::List2(List2* lst)
{
   node* cur = lst->head;
   length = 0;
   while(cur != NULL)
   {
      this->PutItemT(cur->item);
      cur = cur->next;
   }
}

List2::~List2()
{
   while(!this->IsEmpty())
   {
      this->DeleteItemH();
   }
   head = NULL;
   tail = NULL;
}

bool List2::IsEmpty() const
{
   if(head == NULL)
   {
      return true;
   }
   return false;  
}

int List2::GetLength() const
{
   return length;
}

itemType List2::GetItemH() const
{
   return head->item;
}

void List2::DeleteItemH()
{
   node *remove = head;
   head = remove->next;
   delete remove;
   
   length -= 1;
}

void List2::PutItemT(itemType newItem)
{
   node *add = new node;
   add->item = newItem;
   
   if(head == NULL)
   {
      head = add;
      tail = add;
   }
   else
   {
      tail->next = add;
      tail = add;
   }
   length += 1;
}

itemType List2::GetItemT()
{
   return tail->item;
}

void List2::DeleteItemT()
{
   node *new_tail = head;
   
   delete tail;
   for(int i = 0; i < (length - 2); i++)
   {
      new_tail = new_tail->next;
   }
   new_tail->next = NULL;
   tail = new_tail;
   
   length -= 1;
}

void List2::Print()
{
   node *cur = head;
   while(cur != NULL)
   {
      cout<<cur->item<<endl;
      cur = cur->next;
   }
}

bool List2::Find(itemType item, int& pos)
{
   node *cur = head;
   for(int i = 0; i < length; i++)
   {
      if(cur->item == item)
      {
         pos = i;
         return true;
      }
      cur = cur->next;
   }   
   pos = -1;
   return false;
}




