//Benjamin Reilly

#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <algorithm>
#include <vector>
#include "collection.h"


template <typename K, typename V>
class  BinSearchCollection : public  Collection <K,V>
{
   public:
      //insert a key-value pair into the collection
      void insert(const K& key, const V& val);
      
      //remove a key-value pair from the collection
      void remove(const K& key);
      
      //find and return the value associated with the key
      bool find(const K& key, V& val) const;
      
      //find and return the list of keys >= to k1 and <= to k2
      void find(const K& k1, const K& k2, std::vector <K>& keys) const;
      
      //return all of the keys in the collection
      void keys(std::vector <K>& keys) const;
      
      //return all of the keys in ascending (sorted) order
      void sort(std::vector <K>& keys) const;
      
      //return the number of keys in collection
      int size() const;
      
      private:
         //helper function for binary search
         bool binsearch(const K& key , int& index)const;
         //vector storage
         std::vector <std::pair <K,V>> kv_list;
};

//This function returns true and sets index if key is found in
//kv_list, and returns false and sets index to where key should go in
//kv_list otherwise. If list is empty, index is unchanged.
template <typename K, typename V>
bool BinSearchCollection<K,V>::binsearch(const K& key , int& index) const
{
   int low = 0, high = kv_list.size() - 1, mid = 0;
   
   if(kv_list.empty())
   {
      return false;
   }
   
   while(high >= low)
   {
      mid = (low + high) / 2;
      if(key < kv_list.at(mid).first)//to the left side
      {
         high = mid - 1;
      }
      else if(kv_list.at(mid).first < key)//to the right side
      {
         low = mid + 1;
      }
      else
      {
         index = mid;
         return true;
      }
   }
   if(key > kv_list.at(mid).first)
   {
      index = mid + 1;
   }
   else
   {
      index = mid;
   }
   return false;
}

//...remaining function implementations here...

template <typename K, typename V>
void BinSearchCollection<K,V>::insert(const K& key, const V& val)
{
   int index = -1;
   std::pair<K,V> p(key, val);
   binsearch(key, index);
   
   if(kv_list.empty())
   {
      kv_list.push_back(p);
   }
   else
   {
      kv_list.insert(kv_list.begin() + index, p);
   }
}

template <typename K, typename V>
void BinSearchCollection<K,V>::remove(const K& key)
{
   int index = -1;
   
   if(binsearch(key, index))
   {
      kv_list.erase(kv_list.begin() + index);
   }
}

template <typename K, typename V>    
bool BinSearchCollection<K,V>::find(const K& key, V& val) const
{
   bool found;
   int index = -1;
   
   found = binsearch(key, index);
   if(found)
   {
      val = kv_list.at(index).second;
   }

   return found;
}

template <typename K, typename V>
void BinSearchCollection<K,V>::find(const K& k1, const K& k2, std::vector <K>& keys) const
{
   int index_k1 = -1, index_k2 = -1;
   if(binsearch(k1, index_k1) && binsearch(k2, index_k2))
   {
      for(int i = index_k1; i <= index_k2; i++)
      {
         keys.push_back(kv_list.at(i).first);
      }
   }
}

template <typename K, typename V> 
void BinSearchCollection<K,V>::keys(std::vector <K>& keys) const
{
   for(int i = 0; i < size(); i++)
      keys.push_back(kv_list.at(i).first);
}

template <typename K, typename V>   
void BinSearchCollection<K,V>::sort(std::vector <K>& keys) const
{
   for(int i = 0; i < size(); i++)
      keys.push_back(kv_list.at(i).first);
}

template <typename K, typename V>
int BinSearchCollection<K,V>::size() const
{
   return kv_list.size();
}

#endif





