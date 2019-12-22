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

List::List()
{
   length = 0;
   head = NULL;
}
List::~List()
{
   while(head != NULL)
   {
      this->DeleteItemH();
   }
}

/*
pre: an instance of lists exists
post: returns true if list is empty, false otherwise
*/ 
bool List::IsEmpty() const
{
   return length;
}

/*
pre: an instance of list exists
post: returns length of the list 
*/
int List::GetLength() const
{
   return length;
}

/*
pre: an instance of list exists
post: newItem is at the head of the list 
*/
void List::PutItemH(const itemType newItem)
{
   node *added_node;
   added_node = new node;
   
   added_node->item = newItem;
   added_node->next = head;
   head = added_node;
   
   length += 1;
}

/*
pre: an instance of list exists and is not empty
post: Returns the contents of the head of the list. 
*/
itemType List::GetItemH() const
{
   return head->item;  
}

/*
pre: an instance of list exists and is not empty
post: head of the list is deleted 
*/
void List::DeleteItemH()
{
   node *current;
   current = head;
   head = head->next;
   
   delete current;
   current = NULL;
   
   length -= 1;
}

/*
pre: an instance of list exists and is not empty
post: contents of list nodes are displayed on subsequent lines 
*/
void List::Print() const
{
   node *current = head;
   
   while(current != NULL)
   {
      cout<<current->item<<endl;
      current = current->next;
   }
}
