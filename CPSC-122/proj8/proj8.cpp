/*
Class: CPSC122-01
Team Member 1: Benjamin Reilly
Team Member 2: N/a
Submitted By: Benjamin Reilly
GU Username: breilly4
File Name: proj8.cpp
To Build: g++ proj8.cpp
To Execute: ./a.out
*/

#include "proj8.h"
#include <iostream>

using namespace std;

List3::List3()
{
   head = NULL;
   length = 0;
}

/*
pre: an instance of what lst points to exists
post: the list created with the constructor contains the contents of
      what lst points to
*/
List3::List3(List3* lst)
{
   int prev_length = lst->GetLength();
   
   length = 0;
   head = NULL;
   
   for(int i = 0; i < prev_length; i++)
   {
      PutItem(i + 1, lst->GetItem(i + 1));
   }
}

/*
pre: an instance of List exists
post: memory for all nodes in List have been returned to the heap
*/
List3::~List3()
{
   while(length > 0)
   {
      DeleteItem(1);
   }
   head = NULL;
}

/*
pre: an instance of lists exists
post: returns true if list is empty, false otherwise
*/
bool List3::IsEmpty() const
{
   return length;
}

/*
pre: an instance of list exists
post: returns length of the list
*/
int List3::GetLength() const
{
   return length;
}

/*
pre: an instance of list exists,pos >= 0
post: item is at posiiton pos of the list
*/
void List3::PutItem(int pos, itemType item)
{
   node *current;
   node *add = new node;
   
   if(pos == 1)
   {
      add->next = head;
      head = add;
   }
   else
   {
      current = ptrTo(pos - 1);
      add->next = current->next;
      current->next = add;
   }
   
   add->item = item;
   length += 1;
}

/*
pre: an instance of list exist, is not empty, pos >= 0
post: returns the contents of the list at positon pos
*/
itemType List3::GetItem(int pos)
{
   node *current;
   current = ptrTo(pos);
   return current->item;
}

/*
pre: an instance of list exists, is not empty, pos >= 0
post: item at position, pos, is deleted, memory is returned to the heap
*/
void List3::DeleteItem(int pos)
{
   node *remove;
   node *current = head;
   if(pos == 1)
   {
      remove = head;
      head = ptrTo(2);
   }
   else
   {
      current = ptrTo(pos - 1);
      remove = current->next;
      current->next = remove->next;
   }
   delete remove;
   length -= 1;
}

/*
use: displays the contents of the list on the screen
pre: an instance of list exists and is not empty
post: contents of list nodes are displayed on subsequent lines
*/
void List3::Print()
{
   node *current = head;
   int index = 1;
   while(current != NULL)
   {
      cout<<current->item<<endl;
      current = current->next;
   }
}

/*
pre: an instance of list exists, pos >= 0
post: Returns the address of the node in position pos
*/
node* List3::ptrTo(int pos)
{
   node *current = head;
   for(int i = 0; i < pos - 1; i++)
   {
      current = current->next;
   }
   return current;
}






