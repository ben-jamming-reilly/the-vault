//Benjamin Reilly

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"


template <typename K, typename V>
class LinkedListCollection : public Collection <K,V>
{
   public:
      //create an empty linked list
      LinkedListCollection();
      
      //copy a linked list
      LinkedListCollection(const LinkedListCollection <K,V>& rhs);
      
      //assign a linked list
      LinkedListCollection <K,V>& operator=(const LinkedListCollection <K,V>& rhs);
      
      //delete a linked list
      ~LinkedListCollection();
      
      //insert a key-value pair into the collection
      void insert(const K& key, const V& val);
      
      //remove a key-value pair from the collection
      void remove(const K& key);
      
      //find the value associated with the key
      bool find(const K& key ,V& val) const;
      
      //find the keys associated with the range
      void find(const K& k1, const K& k2, std::vector<K>& keys) const;
      
      //return all keys in the collection
      void keys(std::vector <K>& keys) const;
      
      //return collection keys in sorted order
      void sort(std::vector<K>& keys) const;
      
      //return the number of keys in collection
      int size() const;
      
      //in place sorting
      void insertion_sort();
      void merge_sort();
      void quick_sort();
      
   private:
      //linked list node structure
      struct Node
      {
         K key;
         V value;
         Node* next;
      };
      Node* head;
      Node* tail;
      int length;
      
      //helper to delete linked list
      void make_empty();
      
      // merge sort helper(see course notes for details)
      Node* merge_sort(Node* left, int len);
      
      //quick sort helper(see course notes for details)
      Node* quick_sort(Node* start, int  len);
};

//==========================================
//                 HW_6
//==========================================

template <typename K, typename V>
void LinkedListCollection<K,V>::make_empty()
{
   Node *cur = head,
        *cur_prev = nullptr;
   while(cur != nullptr)
   {
      cur_prev = cur;
      cur = cur->next;
      delete cur_prev;
   }
   
   length = 0;
   head = nullptr;
   tail = nullptr;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{   
   Node *cur = head, *cur_prev = nullptr;

   if(cur ==  nullptr)//checks if empty
      return;
   
   cur_prev = cur;
   cur = cur->next;
   
   while(cur != nullptr)
   {
      Node **compare_ptr;
      compare_ptr = &head;
      
      while(*compare_ptr != cur)
      {
         if((*compare_ptr)->key > cur->key)
         {
            cur_prev->next = cur->next;
            if(cur == tail)
               tail = cur_prev;
            cur->next = *compare_ptr;
            *compare_ptr = cur;
            
            cur = cur_prev;
            break;
         }
         compare_ptr = &((*compare_ptr)->next);
      }
      cur_prev = cur;
      cur = cur->next;
   }
}

template <typename K,typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection <K,V>::merge_sort(Node* left, int len)
{
   Node *left_cur, *right_cur;
   Node **cur_ptr;
   int left_len, right_len;
   
   if(len > 1)
   {
      left_len = len / 2;
      right_len = (len / 2) + (len % 2);
      
      left_cur = left;
      right_cur = left;
      for(int i = 0; i < left_len; i++)
         right_cur = right_cur->next;
      
      //returns a sorted left list
      left_cur = merge_sort(left_cur, left_len);
      
      //returns a sorted right list
      right_cur = merge_sort(right_cur, right_len);
      
      cur_ptr = &left;
      while(left_len > 0 && right_len > 0)
      {
         if(left_cur->key < right_cur->key)
         {
            if(left_cur == head)
               head = left;
               
            *cur_ptr = left_cur;
            left_cur = left_cur->next;
            left_len--;
         }
         else
         {
            if(right_cur == head)
               head = left;
            
            *cur_ptr = right_cur;
            right_cur = right_cur->next;
            right_len--;
         }
         cur_ptr = &((*cur_ptr)->next);
      }
      while(left_len > 0)
      {
         if(left_cur == head)
            head = left;
         
         *cur_ptr = left_cur;
         left_cur = left_cur->next;
         left_len--;
         
         //sets tail pointer to last noded
         //added into the sorted list 
         if(left_len == 0)
            tail = *cur_ptr;
         
         cur_ptr = &((*cur_ptr)->next);
         
         if(left_len == 0)
            *cur_ptr = nullptr;
      }
      while(right_len > 0)
      {
         if(right_cur == head)
            head = left;
         
         *cur_ptr = right_cur;
         right_cur = right_cur->next;
         right_len--;
         
         //sets tail pointer to last noded
         //added into the sorted list 
         if(right_len == 0)
            tail = *cur_ptr;
         
         cur_ptr = &((*cur_ptr)->next);
         
         if(right_len == 0)
            *cur_ptr = nullptr;
      }
   }
   return left;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{
   head = merge_sort(head, length);
}

template <typename K, typename V>
typename LinkedListCollection <K,V>::Node*
LinkedListCollection <K,V>::quick_sort(Node* start, int len)
{
   Node *pivot, *left_start = nullptr, *right_start = nullptr,
        *cur, *new_start;
   int left_size = 0, right_size = 0;
   bool found_tail = false;
   
   if(len > 1)
   {
      pivot = start;
      cur = start->next;
      
      for(int i = 0; i < len - 1; i++)
      {
         Node *next_node = cur->next;
         if(cur == tail)
            found_tail = true;
         
         if(cur->key < pivot->key)
         {
            cur->next = left_start;
            left_start = cur;
            left_size++;
         }
         else
         {
            cur->next = right_start;
            right_start = cur;
            right_size++;
         }
         cur = next_node;
      }
      
      left_start = quick_sort(left_start, left_size);
      right_start = quick_sort(right_start, right_size);
      
      if(left_start != nullptr)
      {
         new_start = left_start;
         cur = new_start;
         
         for(int i = 0; i < left_size - 1; i++)
            cur = cur->next;
         
         cur->next = pivot;
         cur = cur->next;
      }
      else
      {
         new_start = pivot;
         cur = new_start;
      }
      cur->next = right_start;
      
      for(int i = 0; i < right_size; i++)
         cur = cur->next;
      
      if(found_tail)
         tail = cur;
      
      cur->next = nullptr;
      
      return new_start;
   }
   return start;
}

template <typename K, typename V>
void LinkedListCollection <K,V>::quick_sort()
{
   head = quick_sort(head, length);
}

//==========================================
//                 HW_4
//==========================================

template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
{
   head = nullptr;
   tail = nullptr;
   length = 0;
}

template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection <K,V>& rhs)
{
   head = nullptr;
   tail = nullptr;
   length = 0;
   
   Node *cur = rhs.head;
   
   while(cur != nullptr)
   {
      insert(cur->key, cur->value);
      cur = cur->next;
   }
}
template <typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection <K,V>& rhs)
{
   Node *cur = head,
        *cur_prev = nullptr;
   if(this != &rhs)
   {
      make_empty();
      cur = rhs.head;
      while(cur != nullptr)
      {
         insert(cur->key, cur->value);
         cur = cur->next;
      }
   }
   return *this;
}
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
   make_empty();
}

template <typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& key, const V& val)
{
   Node *add = new Node;
   
   add->key = key;
   add->value = val;
   add->next = nullptr;
   
   if(length == 0)
   {
      head = add;
      tail = add;
   }
   else
   {
      tail->next = add;
      tail = add;
   }
   
   length++;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& key)
{
   Node *cur = head,
        *cur_prev = nullptr;
   
   while(cur != nullptr)
   {
      if(cur->key == key)
         break;
      
      cur_prev = cur;
      cur = cur->next;
   }
   
   if(cur != nullptr)
   {
      if(cur == head)
      {
         head = cur->next;
      }
      else if(cur == tail)
      {
         tail = cur_prev;
         cur_prev->next = nullptr;
      }
      else
      {
         cur_prev->next = cur->next;
      }
      delete cur;
      length--;
   }
}

template <typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& key, V& val) const
{
   Node *cur = head;
   while(cur != nullptr)
   {
      if(cur->key == key)
      {
         val = cur->value;
         return true;
      }
      cur = cur->next;
   }
   return false;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector <K>& keys) const
{
   Node *cur = head;
   while(cur != nullptr && cur->key != k1)
   {
      cur = cur->next;
   }
   while(cur != nullptr)
   {
      keys.push_back(cur->key);
      if(k2 == cur->key)
         break;
      cur = cur->next;
   }
}

template <typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector <K>& keys) const
{
   Node *cur = head;
   while(cur != nullptr)
   {
      keys.push_back(cur->key);
      cur = cur->next;
   }
}

template <typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector <K>& keys) const
{
   Node* ptr = head;
   while (ptr !=  nullptr)
   {
      keys.push_back(ptr ->key);
      ptr = ptr ->next;
   }
   std::sort(keys.begin(), keys.end());
}

template <typename K, typename V>
int LinkedListCollection<K,V>::size() const
{
   return length;
}

#endif