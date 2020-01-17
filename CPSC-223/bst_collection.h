//Benjamin Reilly

#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include "collection.h"
#include <algorithm>

template <typename K, typename V>
class BSTCollection : public Collection <K,V>
{
   public:
      // create an empty linked list
      BSTCollection ();
      
      // copy a linked list
      BSTCollection(const BSTCollection <K,V>& rhs);
      
      // assign a linked list
      BSTCollection <K,V>& operator=(const BSTCollection <K,V>& rhs);
      
      // delete a linked list
      ~BSTCollection ();
      
      // insert a key -value pair into the collection
      void insert(const K& key , const V& val);
      
      // remove a key -value pair from the collection
      void remove(const K& key);
      
      // find the value associated with the key
      bool find(const K& key , V& val) const;
      
      // find the keys associated with the range
      void find(const K& k1, const K& k2, std::vector <K>& keys) const;
      
      // return all keys in the collection
      void keys(std::vector <K>& keys) const;
      
      // return collection keys in sorted order
      void sort(std::vector <K>& keys) const;
      
      // return the number of keys in collection
      int size() const;
      
      // return the height of the tree
      int height() const;
   
   private:
      // binary search tree node structure
      struct Node
      {
         K key;
         V value;
         Node* left;
         Node* right;
      };
      
      // root node of the search tree
      Node* root;
      
      // number of k-v pairs in the collection
      int collection_size;
      
      // helper to recursively empty search tree
      void make_empty(Node* subtree_root);
      
      // helper to recursively build sorted list of keys
      void inorder(const Node* subtree, std::vector <K>& keys) const;
      
      // helper to recursively build sorted list of keys
      void preorder(const Node* subtree, std::vector <K>& keys) const;
      
      // helper to recursively find range of keys
      void range_search(const Node* subtree, const K& k1, const K& k2, std::vector <K>& keys) const;
      
      // helper to recursively remove key node from subtree
      Node* remove(const K& key, Node* subtree_root);
      
      // return the height of the tree rooted at subtree_root
      int height(const Node* subtree_root) const;
};


template <typename K, typename V>
BSTCollection<K,V>::BSTCollection():
collection_size (0), root(nullptr)
{}

template <typename K, typename V>
void BSTCollection<K,V>::make_empty(Node* subtree_root)
{
   if(subtree_root != nullptr)
   {
      make_empty(subtree_root->left);
      make_empty(subtree_root->right);
      delete subtree_root;
      collection_size--;
   }
}

template <typename K, typename V>
BSTCollection<K,V>::~BSTCollection()
{
   make_empty(root);
   root = nullptr;
}

template <typename K, typename V>
BSTCollection<K,V>::BSTCollection(const BSTCollection <K,V>& rhs)
:collection_size(0), root(nullptr)
{
   *this = rhs;
}

template <typename K, typename V>
BSTCollection <K,V>& BSTCollection<K,V>::operator=(const BSTCollection <K,V>& rhs)
{
   if (this == &rhs)
      return *this;
   
   // delete current
   make_empty(root);
   root = nullptr;
   
   // build tree
   std::vector <K> ks;
   preorder(rhs.root, ks);
   
   for(K key : ks)
   {
      V v_find;
      rhs.find(key, v_find);
      insert(key, v_find);
   }
   return *this;
}


template <typename K, typename V>
void BSTCollection<K,V>::insert(const K& key, const V& val)
{
   Node **cur_ptr = &root;
   
   //searches for an open spot in bst
   while(*cur_ptr != nullptr)
   {
      if((*cur_ptr)->key < key)
      {
         //go to right subtree
         cur_ptr = &((*cur_ptr)->right);
      }
      else
      {
         //go to left subtree
         cur_ptr = &((*cur_ptr)->left);
      }
   }
   
   //adds node in bst
   *cur_ptr = new Node();
   (*cur_ptr)->key = key;
   (*cur_ptr)->value = val;
   (*cur_ptr)->left = nullptr;
   (*cur_ptr)->right = nullptr;
   collection_size++;
}

template <typename K, typename V>
void BSTCollection<K,V>::remove(const K& key)
{
   root = remove(key, root);
}

template <typename K, typename V>
bool BSTCollection <K,V>::find(const K& key, V& val) const
{
   Node* cur = root;
   while(cur != nullptr)
   {
      if(cur->key == key)
      {
         val = cur->value;
         return true;
      }
      
      if(cur->key < key)
      {
         cur = cur->right;
      }
      else  //key <= cur->key
      {
         cur = cur->left;
      }
   }
   return false;
}

template <typename K, typename V> 
void BSTCollection <K,V>::
range_search(const Node* subtree, const K& k1, const K& k2, std::vector <K>& ks) const
{
   bool greater_k1 = false, less_k2 = false;
   if(subtree != nullptr)
   {
      if(k1 <= subtree->key)
      {
         greater_k1 = true;
         range_search(subtree->left, k1, k2, ks);
      }
      
      if(subtree->key <= k2)
      {
         less_k2 = true;
         range_search(subtree->right, k1, k2, ks);
      }
      
      if(greater_k1 && less_k2)
         ks.push_back(subtree->key);
   }
}

template <typename K, typename V> 
void BSTCollection<K,V>::find(const K& k1, const K& k2, std::vector <K>& ks) const
{
   // defer to the range search (recursive) helper function
   range_search(root, k1, k2, ks);
}

template <typename K, typename V>
void BSTCollection<K,V>::inorder(const Node* subtree, std::vector <K>& ks) const
{
   if(subtree != nullptr)
   {
      inorder(subtree->left, ks);
      ks.push_back(subtree->key);
      inorder(subtree->right, ks);
   }
}

template <typename K, typename V>
void BSTCollection<K,V>::preorder(const Node* subtree, std::vector <K>& ks) const
{
   if(subtree != nullptr)
   {
      ks.push_back(subtree->key);
      preorder(subtree->left, ks);
      preorder(subtree->right, ks);
   }
}

template <typename K, typename V>
void BSTCollection<K,V>::keys(std::vector <K>& ks) const
{
   // defer to the inorder (recursive) helper function
   inorder(root, ks);
}

template <typename K, typename V>
void BSTCollection<K,V>::sort(std::vector <K>& ks) const
{
   // defer to the inorder (recursive) helper function
   inorder(root, ks);
}

template <typename K, typename V>
int BSTCollection<K,V>::size() const
{
   return collection_size;
}

template <typename K, typename V>
int BSTCollection<K,V>::height(const Node* subtree_root) const
{
   int left_height = 0, right_height = 0;
   
   if(subtree_root == nullptr)
   {
      return 0;
   }
   else
   {
      left_height = height(subtree_root->left);
      right_height = height(subtree_root->right);
      
      if(left_height > right_height)
      {
         return left_height + 1;
      }
      return right_height + 1;
   }
}

template <typename K, typename V>
typename BSTCollection <K,V>::Node*
BSTCollection <K,V>::remove(const K& key, Node* subtree_root)
{
   if(subtree_root && key < subtree_root->key)
   {
      subtree_root->left = remove(key, subtree_root->left);
   }
   else if(subtree_root && key > subtree_root->key)
   {
      subtree_root->right = remove(key, subtree_root->right);
   }
   else if(subtree_root && key == subtree_root->key)
   {
      if(!subtree_root->left && !subtree_root->right)
      {
         //leaf node
         delete subtree_root;
         collection_size--;
         subtree_root = nullptr;
      }
      else if(subtree_root->left && subtree_root->right)
      {
         //two children
         Node **ptr_successor = &(subtree_root->right);
         while((*ptr_successor)->left != nullptr)
            ptr_successor = &((*ptr_successor)->left);
         
         //copies successor
         subtree_root->value = (*ptr_successor)->value;
         subtree_root->key = (*ptr_successor)->key;
         
         if((*ptr_successor)->right)
         {
            //removes single child successor
            Node *remove = *ptr_successor;
            *ptr_successor = remove->right;
            delete remove;
            collection_size--;
         }
         else
         {
            //removes leaf successor
            delete (*ptr_successor);
            collection_size--;
            *ptr_successor = nullptr;
         }
      }
      else
      {
         //single child
         Node *remove = subtree_root;
         if(remove->left)
            subtree_root = remove->left;
         else
            subtree_root = remove->right;
         
         delete remove;
         collection_size--;
      }
   }
   return subtree_root;
}

template <typename K, typename V>
int BSTCollection<K,V>::height() const
{
   // defer to the height (recursive) helper function
   return height(root);
}

#endif