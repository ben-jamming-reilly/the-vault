//Benjamin Reilly
//CPSC 223-01

#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"

template <typename K, typename V>
class HashTableCollection : public Collection <K,V>
{
   public:
      //create an empty linked list
      HashTableCollection();
      
      //copy a linked list
      HashTableCollection(const HashTableCollection <K,V>& rhs);
      
      //assign a linked list
      HashTableCollection <K,V>& operator=(const HashTableCollection <K,V>& rhs);
      
      //delete a linked list
      ~HashTableCollection();
      
      //insert a key-value pair into the collection
      void insert(const K& key, const V& val);
      
      //remove a key-value pair from the collection
      void remove(const K& key);
      
      //find the value associated with the key
      bool find(const K& key, V& val) const;
      
      //find the keys associated with the range
      void find(const K& k1, const K& k2, std::vector <K>& keys) const;
      
      //return all keys in the collection
      void keys(std::vector <K>& keys) const;
      
      //return collection keys in sorted order
      void sort(std::vector <K>& keys) const;
      
      //return the number of keys in collection
      int size() const;
      
   private:
      //helper to empty entire hash table
      void make_empty ();
      
      //resize and rehash the hash table
      void resize_and_rehash ();
      
      //linked list node structure
      struct Node
      {
         K key;
         V value;
         Node* next;
      };
      
      //number of k-v pairs in the collection
      int collection_size;
      
      //number of hash table buckets(default is 16)
      int table_capacity;
      
      //hash table array load factor (set at 75% for resizing)
      const double load_factor_threshold;
      
      // hash table array
      Node** hash_table;
};


template <typename K, typename V>
HashTableCollection <K,V>::HashTableCollection():
collection_size (0), table_capacity (16), load_factor_threshold (0.75)
{
   //dynamically allocate the hash table array
   hash_table = new Node*[table_capacity];
   // initialize the hash table chains
   for(int i = 0; i < table_capacity; ++i)
      hash_table[i] = nullptr;
}

template <typename K, typename V>
void HashTableCollection <K,V>::make_empty()
{
   //make sure hash table exists
   if(hash_table == nullptr)
      return;
   
   //remove each key
   for(int i = 0; i < table_capacity; i++)
   {
      Node *bucket_head = *(hash_table + i);
      while(bucket_head != nullptr)
      {
         Node *remove = bucket_head;
         bucket_head = remove->next;
         delete remove;
      }
   }

   //remove the hash table
   delete hash_table;
}

template <typename K, typename V>
HashTableCollection <K,V>::~HashTableCollection()
{
   make_empty();
}


template <typename K, typename V>
HashTableCollection <K,V>::HashTableCollection(const HashTableCollection <K,V>& rhs)
:hash_table(nullptr)
{
   *this = rhs;
}

template <typename K, typename V>
HashTableCollection <K,V>&
HashTableCollection <K,V>::operator=(const HashTableCollection <K,V>& rhs)
{
   //check if rhs is current object and return current object
   if(this == &rhs)
      return *this;
   
   //delete current object
   make_empty();
   
   //initialize current object
   hash_table = new Node*[rhs.table_capacity];
   
   //create the hash table
   for(int i = 0; i < rhs.table_capacity; i++)
      hash_table[i] = nullptr;
   
   //do the copy
   for(int i = 0; i < rhs.table_capacity; i++)
   {
      Node *rhs_cur = *(rhs.hash_table + i);
      Node **cur_ptr = (hash_table + i);
      
      while(rhs_cur != nullptr)
      {
         //make identical node
         Node *add = new Node;
         add->key = rhs_cur->key;
         add->value = rhs_cur->value;
         add->next = nullptr;
         
         //place it with in the list
         *cur_ptr = add; 
         
         cur_ptr = &((*cur_ptr)->next);
         rhs_cur = rhs_cur->next;
      }
   }
   collection_size = rhs.collection_size;
   table_capacity = rhs.table_capacity;
   
   //NEED TO CATCH IF ASSIGNMENT COMES FROM
   //AN EMPTY LIST
   return *this;
}

template <typename K, typename V>
void HashTableCollection <K,V>::resize_and_rehash()
{
   //setup new table
   int new_capacity = table_capacity * 2;
   //... similarly with collection size ...
   //dynamically allocate the new table
   
   Node** new_table = new Node*[new_capacity];
   
   //initialize new table
   for(int i = 0; i < new_capacity; i++)
      new_table[i] = nullptr;
   
   //insert key values
   std::vector <K> ks;
   keys(ks);
   
   for(K key : ks)
   {
      //hash the key
      std::hash<K> hash_func;
      std::size_t code = hash_func(key);
      std::size_t hash_index = code % new_capacity;
      
      //create a new node in new table
      V find_value;
      find(key, find_value);
      
      Node *add = new Node;
      add->key = key;
      add->value = find_value;
      
      add->next = *(new_table + hash_index);
      *(new_table + hash_index) = add;
      
   }
   //clear the current data
   make_empty();
   //update to the new settings
   hash_table = new_table;
   
   //... update remaining vars ...
   table_capacity = new_capacity;
}

template <typename K, typename V>
void HashTableCollection <K,V>::insert(const K& key , const V& val)
{
   //check current load factor versus load factor threshold,
   //and resize and copy if necessary by calling resize_and_rehash()
   double load_factor = collection_size / table_capacity;
   
   if(load_factor > load_factor_threshold)
      resize_and_rehash();
   
   //hash the key
   std::hash<K> hash_func;
   std::size_t code = hash_func(key);
   std::size_t hash_index = code % table_capacity;
   
   //create the new node
   Node* add = new Node;
   add->key = key;
   add->value = val;
   add->next = *(hash_table + hash_index);
   *(hash_table + hash_index) = add;
   
   //update the size
   collection_size++;
}

template <typename K, typename V>
void HashTableCollection <K,V>::remove(const K& key)
{
   Node **cur_ptr;
   
   std::hash<K> hash_func;
   std::size_t code = hash_func(key);
   std::size_t hash_index = code % table_capacity;
   
   //points to memory address of the 1st node in the chain.
   cur_ptr = &(*(hash_table + hash_index));
   
   while(*cur_ptr != nullptr)
   {
      Node *remove;
      if((*cur_ptr)->key == key)
      {
         remove = *cur_ptr;
         *cur_ptr = remove->next;
         delete remove;
         collection_size--;
         break;
      }
      cur_ptr = &((*cur_ptr)->next);
   }
}

template <typename K, typename V>
bool HashTableCollection <K,V>::find(const K& key, V& val) const
{
   Node *cur;
   std::hash<K> hash_func;
   std::size_t code = hash_func(key);
   std::size_t hash_index = code % table_capacity;
   
   //cur now head of corresponding chain
   cur = *(hash_table + hash_index);
   
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
void HashTableCollection <K,V>::find(const K& k1, const K& k2, std::vector <K>& keys) const
{
   int i = 0;
   std::vector<K> sorted_keys;
   sort(sorted_keys);
   
   while(i < sorted_keys.size())
   {
      if(sorted_keys.at(i) != k1)
         break;
      i++;
   }
   while(i < sorted_keys.size())
   {
      keys.push_back(sorted_keys.at(i));
      if(sorted_keys.at(i) == k2)
         break;
      i++;
   }
}

template <typename K, typename V>
void HashTableCollection <K,V>::keys(std::vector <K>& keys) const
{
   for(int i = 0; i < table_capacity; i++)
   {
      Node *cur = *(hash_table + i);
      while(cur != nullptr)
      {
         keys.push_back(cur->key);
         cur = cur->next;
      }
   }
}
      
template <typename K, typename V>
void HashTableCollection <K,V>::sort(std::vector <K>& ks) const
{
   keys(ks);
   std::sort(ks.begin(), ks.end());
}

template <typename K, typename V>
int HashTableCollection <K,V>::size() const
{
   return collection_size;
}

#endif