#include "proj9.h"

#include <iostream>


using namespace std;

List4::List4()
{
   head = new doubleNode;
   tail = new doubleNode;
   
   head->prev = NULL;
   head->item = -666;
   head->next = tail;
   
   tail->prev = head;
   tail->item = -666;
   tail->next = NULL;
   
   length = 0;
}
List4::~List4()
{
   doubleNode *current = head->next;
   while(current->next != NULL)
   {
      Delete(1);
      current = head->next;
   }
   delete head;
   delete tail;
}

void List4::Insert(itemType item, int pos)
{
   doubleNode *current, *add;
   add = new doubleNode;
   add->item = item;
   
   current = FindPosition(pos);
   
   add->next = current->next;
   add->prev = current;
   
   current = current->next;
   current->prev = add;
   
   current = current->prev->prev;
   current->next = add;
   
   length += 1;
}

void List4::Delete(int pos)
{
   doubleNode *remove, *current;
   
   remove = FindPosition(pos + 1);
   
   current = remove->prev;
   current->next = remove->next;
   
   current = remove->next;
   current->prev = remove->prev;
   
   delete remove;
   length -= 1;
}

doubleNode* List4::Find(itemType item)
{
   doubleNode *current = head->next;
   while(current->next != NULL)
   {
      if(current->item == item)
      {
         return current;
      }
      current = current->next;
   }
   return NULL;
}

int List4::DeleteItem(itemType item)
{
   int num_removed = 0;
   doubleNode *remove, *current;
   
   remove = Find(item);
   while(remove != NULL)
   {
      current = remove->prev;
      current->next = remove->next;
      
      current = remove->next;
      current->prev = remove->prev;
      
      delete remove;
      length -= 1;
      num_removed += 1;
      
      remove = Find(item);
   }
   return num_removed;
}

void List4::PrintForward()
{
   doubleNode *current = head->next;
   while(current->next != NULL)
   {
      cout<<current->item<<endl;
      current = current->next;
   }
}

void List4::PrintBackwards()
{
   doubleNode *current = tail->prev;
   while(current->prev != NULL)
   {
      cout<<current->item<<endl;
      current = current->prev;
   }
}

void List4::Sort()
{
   itemType sto;
   doubleNode *current, *unsorted_current, *min;
   
   current = head->next;
   while(current->next != NULL)
   {
      unsorted_current = current->next;
      min = current;
      while(unsorted_current->next != NULL)
      {
         if(unsorted_current->item < min->item)
         {
            min = unsorted_current;
         }
         unsorted_current = unsorted_current->next;
      }
      
      sto = current->item;
      current->item = min->item;
      min->item = sto;
      
      current = current->next;
   }
}

//Private

doubleNode* List4::FindPosition(int pos)
{
   doubleNode *ptr;
   if(pos == 1)
   {
      ptr = head;
   }
   else if(pos >= length + 1)
   {
      // >= to ensure no errors arise
      ptr = tail->prev;
   }
   else
   {
      ptr = head;
      for(int i = 1; i < pos; i++)
      {
         ptr = ptr->next;
      }
   }
   return ptr;
}
