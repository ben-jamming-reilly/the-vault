#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

#include <iostream>
using namespace std;

template <typename K, typename V>
class RBTCollection : public Collection <K,V>
{
   public:
      //create an empty linked list
      RBTCollection ();
      
      //copy a linked list
      RBTCollection(const RBTCollection <K,V>& rhs);
      
      //assign a linked list
      RBTCollection <K,V>& operator=(const RBTCollection <K,V>& rhs);
      
      //delete a linked list
      ~RBTCollection();
      
      //insert a key-value pair into the collection
      void insert(const K& key , const V& val);
      
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
      int size()const;
      
      // return the height of the tree
      int height() const;
      
      //optional print function (for testing)
      void print () const;
      
   private:
      //binary search tree node structure
      struct Node
      {
         K key;
         V value;
         Node* left;
         Node* right;
         bool is_black;  // true if black , false if red
         bool is_dbl_black_left; //for remove rotations
         bool is_dbl_black_right; // for remove rotations
      };
      
      //root node of the search tree
      Node* root;
      
      //number of k-v pairs in the collection
      int collection_size;
      
      //helper to recursively empty search tree
      void make_empty(Node* subtree_root);
      
      //recursive helper to remove node with given key
      Node* remove(const K& key, Node* parent, Node* subtree_root, bool& found );
      
      //helper to perform a single rebalance step on a red -black tree on remove
      Node* remove_color_adjust(Node* parent);
      
      //recursive helper to do red-black insert key-val pair (backtracking)
      Node* insert(const K& key, const V& val, Node* subtree_root);
      
      //helper functions to perform a single right rotation
      Node* rotate_right(Node* k2);
      
      //helper functions to perform a single left rotation
      Node* rotate_left(Node* k2);
      
      //helper to recursively build sorted list of keys
      void inorder(const Node* subtree, std::vector <K>& keys) const;
      
      //helper to recursively build sorted list of keys
      void preorder(const Node* subtree, std::vector <K>& keys) const;
      
      //helper to recursively find range of keys
      void range_search(const Node* subtree_root, const K& k1, const K& k2, std::vector <K>& keys) const;
      
      //return the height of the tree rooted at subtree_root
      int height(const Node* subtree_root) const;
};

template <typename K, typename V>
void RBTCollection <K,V>::remove(const K& key)
{
   //check if anything to remove
   if(root == nullptr)
      return;
   //create a "fake" root to pass in as parent of root
   Node* root_parent = new Node();
   root_parent->key = root->key;
   root_parent->left = nullptr;
   root_parent->right = root;
   root_parent->is_black = true;
   root_parent->is_dbl_black_left = false;
   root_parent->is_dbl_black_right = false;
   //call remove
   bool found = false;
   root_parent = remove(key, root_parent, root, found);
   
   //update results
   if(found)
   {
      collection_size--;
      root = root_parent->right;
      if(root)
      {
         root->is_black = true;
         root->is_dbl_black_right = false;
         root->is_dbl_black_left = false;
      }
   }
   delete root_parent;
}

template <typename K, typename V>
typename RBTCollection <K,V>::Node*
RBTCollection <K,V>::remove(const K& key, Node* parent, Node* subtree_root, bool& found)
{
   if(subtree_root && key < subtree_root->key)
   {
      subtree_root = remove(key, subtree_root, subtree_root->left , found);
   }
   else if(subtree_root && key > subtree_root->key)
   {
      subtree_root = remove(key, subtree_root, subtree_root->right, found);
   }
   else if(subtree_root && key == subtree_root->key)
   {
      found = true;
      //leaf node
      if (!subtree_root->left && !subtree_root->right)
      {
         //if node is black then set double-black , adjust parent ,
         //and delete subtree root ...
         
         if(parent->left == subtree_root)
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_left = true;
            
            parent->left = nullptr;
         }
         else
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_right = true;
            
            parent->right = nullptr;
         }
         
         delete subtree_root;
         subtree_root = nullptr;
      }
      //left non-empty but right empty
      else if (subtree_root->left && !subtree_root->right)
      {
         if(parent->left == subtree_root)
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_left = true;
            
            parent->left = subtree_root->left;
         }
         else
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_right = true;
            
            parent->right = subtree_root->left;
         }
         
         delete subtree_root;
         subtree_root = nullptr;
      }
      //left empty but right non-empty
      else if(!subtree_root->left && subtree_root->right)
      {
         if(parent->left == subtree_root)
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_left = true;
            
            parent->left = subtree_root->right;
         }
         else
         {
            if(subtree_root->is_black)
               parent->is_dbl_black_right = true;
            
            parent->right = subtree_root->right;
         } 
         
         delete subtree_root;
         subtree_root = nullptr;
      }
      // left and right non empty
      else
      {
         Node *successor = subtree_root->right;
         K successor_key;
         V successor_val;
         
         bool found_successor = false;
         while(successor->left)
            successor = successor->left;
         
         successor_key = successor->key;
         successor_val = successor->value;
         
         //Perform the remove
         remove(successor_key, parent, subtree_root, found_successor);
         
         subtree_root->key = successor_key;
         subtree_root->value = successor->value;
      }
   }
   
   if(!found)
      return parent;
   
   //backtracking, adjust color at parent
   return remove_color_adjust(parent);
}

template <typename K, typename V>
typename RBTCollection <K,V>::Node*
RBTCollection<K,V>::remove_color_adjust(Node* subtree_root)
{
   //subtree root is "grandparent" g, with left child gl and right child gr
   Node* g = subtree_root;
   Node* gl = g->left;
   Node* gr = g->right;
   
   //parent p is either gl or gr
   Node* p = nullptr;
   bool left_parent = false;
   if (gl && (gl->is_dbl_black_left || gl->is_dbl_black_right ))
   {
      p = gl;
      left_parent = true;
   }
   else if(gr && (gr->is_dbl_black_left || gr->is_dbl_black_right))
      p = gr;
   else
      return subtree_root;
   
   //parent’s left child is a double black node
   if(p->is_dbl_black_left)
   {
      //do the following cases
      
      //case 1: red sibling
      if(p->right && !(p->right)->is_black)
      {
         p = rotate_left(p);
         (p->left)->is_black = false;
         return remove_color_adjust(p->left);
      }
      //case 2: black sibling with red child (outside)
      else if(p->right && (p->right)->right && !((p->right)->right)->is_black)
      {
         p = rotate_left(p);
         if((p->left)->is_black)
         {
            p->is_black = true;
         }
         else
         {
            (p->left)->is_black = true;
            p->is_black = false;
         }
      }
      //case 2: black sibling with red child (inside)
      else if(p->right && (p->right)->left && !((p->right)->left)->is_black)
      {
         p->right = rotate_right(p->right);
         p = rotate_left(p);
         
         if((p->left)->is_black)
         {
            p->is_black = true;
         }
         else
         {
            (p->left)->is_black = true;
            p->is_black = false;
         }
      }
      //case 3: black sibling with black children, red parent
      else if(!p->is_black)
      {
         p->is_black = true;
         if(p->right)
            (p->right)->is_black = false;
      }
      //case 3: black sibling with black children, black parent
      else
      {
         if(left_parent)
            g->is_dbl_black_left = true;
         else
            g->is_dbl_black_right = true;
         
         if(p->right)
            (p->right)->is_black = false;
      }
   }
   
   //parent’s right child is a double black node
   if(p->is_dbl_black_right)
   {
      //do the following cases
      
      //case 1: red sibling
      if(p->left && !(p->left)->is_black)
      {
         p = rotate_right(p);
         (p->right)->is_black = false;
         return remove_color_adjust(p->right);
      }
      //case 2: black sibling with red child (outside)
      else if(p->left && (p->left)->left && !((p->left)->left)->is_black)
      {
         p = rotate_right(p);
         if((p->right)->is_black)
         {
            p->is_black = true;
         }
         else
         {
            (p->right)->is_black = true;
            p->is_black = false;
         }
      }
      //case 2: black sibling with red child (inside)
      else if(p->left && (p->left)->right && !((p->left)->right)->is_black)
      {
         p->left = rotate_left(p->left);
         p = rotate_right(p);
         if((p->right)->is_black)
         {
            p->is_black = true;
         }
         else
         {
            (p->right)->is_black = true;
            p->is_black = false;
         }
      }
      //case 3: black sibling with black children, red parent
      else if(!p->is_black)
      {
         p->is_black = true;
         if(p->left)
            (p->left)->is_black = false;
      }
      //case 3: black sibling with black children, black parent
      else
      {
         if(left_parent)
            g->is_dbl_black_left = true;
         else
            g->is_dbl_black_right = true;
         
         if(p->left)
            (p->left)->is_black = false;
      }
   }
   //connect up the subtree_root to the parent
   if(left_parent)
      subtree_root->left = p;
   else
      subtree_root->right = p;
   return subtree_root;
}

//==================================================================
//
//                            HW_10
//
//==================================================================


template <typename K, typename V>
RBTCollection<K,V>::RBTCollection():
collection_size (0), root(nullptr)
{}

template <typename K, typename V>
void RBTCollection<K,V>::make_empty(Node* subtree_root)
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
RBTCollection<K,V>::~RBTCollection()
{
   make_empty(root);
   root = nullptr;
}

template <typename K, typename V>
RBTCollection<K,V>::RBTCollection(const RBTCollection <K,V>& rhs)
:collection_size(0), root(nullptr)
{
   *this = rhs;
}

template <typename K, typename V>
RBTCollection <K,V>& RBTCollection<K,V>::operator=(const RBTCollection <K,V>& rhs)
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
bool RBTCollection <K,V>::find(const K& key, V& val) const
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
         cur = cur->right;
      else  //key <= cur->key
         cur = cur->left;
   }
   return false;
}

template <typename K, typename V> 
void RBTCollection <K,V>::
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
void RBTCollection<K,V>::find(const K& k1, const K& k2, std::vector <K>& ks) const
{
   // defer to the range search (recursive) helper function
   range_search(root, k1, k2, ks);
}

template <typename K, typename V>
void RBTCollection<K,V>::inorder(const Node* subtree, std::vector <K>& ks) const
{
   if(subtree != nullptr)
   {
      inorder(subtree->left, ks);
      ks.push_back(subtree->key);
      inorder(subtree->right, ks);
   }
}

template <typename K, typename V>
void RBTCollection<K,V>::preorder(const Node* subtree, std::vector <K>& ks) const
{
   if(subtree != nullptr)
   {
      ks.push_back(subtree->key);
      preorder(subtree->left, ks);
      preorder(subtree->right, ks);
   }
}

template <typename K, typename V>
void RBTCollection<K,V>::keys(std::vector <K>& ks) const
{
   // defer to the inorder (recursive) helper function
   inorder(root, ks);
}

template <typename K, typename V>
void RBTCollection<K,V>::sort(std::vector <K>& ks) const
{
   // defer to the inorder (recursive) helper function
   inorder(root, ks);
}

template <typename K, typename V>
int RBTCollection<K,V>::size() const
{
   return collection_size;
}

template <typename K, typename V>
int RBTCollection<K,V>::height(const Node* subtree_root) const
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
int RBTCollection<K,V>::height() const
{
   // defer to the height (recursive) helper function
   return height(root);
}

template <typename K, typename V>
typename RBTCollection <K,V>::Node* RBTCollection <K,V>::rotate_right(Node* k2)
{
   Node* new_subtree_root = k2->left;
   k2->left = new_subtree_root->right;
   new_subtree_root->right = k2;
   return new_subtree_root;
}

template <typename K, typename V>
typename RBTCollection <K,V>::Node* RBTCollection <K,V>::rotate_left(Node* k2)
{
   Node* new_subtree_root = k2->right;
   k2->right = new_subtree_root->left;
   new_subtree_root->left = k2;
   
   return new_subtree_root;
}

template <typename K, typename V>
typename RBTCollection <K,V>::Node*
RBTCollection <K,V>::insert(const K& key, const V& val, Node* subtree_root)
{
   //insert part
   if(subtree_root == nullptr)
   {
      //insert node
      Node *add = new Node();
      
      add->key = key;
      add->value = val;
      add->is_black = false;
      add->is_dbl_black_left = false;
      add->is_dbl_black_right = false;
      subtree_root = add;
      
      return subtree_root;
   }
   else if(key < subtree_root->key)
   {
      //move left
      subtree_root->left = insert(key, val, subtree_root->left);
   }
   else if(subtree_root->key < key)
   {
      //move right
      subtree_root->right = insert(key, val, subtree_root->right);
   }
   
   //No re-balancing on 
   if(subtree_root->is_black == false)
      return subtree_root;
   
   if(subtree_root->left && (subtree_root->left)->is_black == false)
   {
      if((subtree_root->left)->left && ((subtree_root->left)->left)->is_black == false)
      {
         //left-left inbalance
         if(subtree_root->right == nullptr || (subtree_root->right)->is_black)
         {
            subtree_root = rotate_right(subtree_root);
            
            subtree_root->is_black = true;
            (subtree_root->right)->is_black = false;
         }
         else
         {
            subtree_root->is_black = false;
            (subtree_root->left)->is_black = true;
            (subtree_root->right)->is_black = true;
         }
      }
      else if((subtree_root->left)->right && ((subtree_root->left)->right)->is_black == false)
      {
         //left-right inbalance
         if(subtree_root->right == nullptr || (subtree_root->right)->is_black)
         {
            subtree_root->left = rotate_left(subtree_root->left);
            subtree_root = rotate_right(subtree_root);
            
            subtree_root->is_black = true;
            (subtree_root->right)->is_black = false;
         }
         else
         {
            subtree_root->is_black = false;
            (subtree_root->left)->is_black = true;
            (subtree_root->right)->is_black = true;
         }
      }
   }
   else if(subtree_root->right && (subtree_root->right)->is_black == false)
   {
      if((subtree_root->right)->left && ((subtree_root->right)->left)->is_black == false)
      {
         //right-left inbalance
         if(subtree_root->left == nullptr || (subtree_root->left)->is_black)
         {
            subtree_root->right = rotate_right(subtree_root->right);
            subtree_root = rotate_left(subtree_root);
            
            subtree_root->is_black = true;
            (subtree_root->left)->is_black = false;
         }
         else
         {
            subtree_root->is_black = false;
            (subtree_root->left)->is_black = true;
            (subtree_root->right)->is_black = true;
         }

      }
      else if((subtree_root->right)->right && ((subtree_root->right)->right)->is_black == false)
      {
         //right-right inbalance
         if(subtree_root->left == nullptr || (subtree_root->left)->is_black)
         {
            subtree_root = rotate_left(subtree_root);
            
            subtree_root->is_black = true;
            (subtree_root->left)->is_black = false;
         }
         else
         {
            subtree_root->is_black = false;
            (subtree_root->left)->is_black = true;
            (subtree_root->right)->is_black = true;
         }
      }
   }
   return subtree_root;
}

template <typename K, typename V>
void RBTCollection <K,V>::insert(const K& key, const V& val)
{
   root = insert(key, val, root);
   root->is_black = true;
   collection_size++;
}

#endif