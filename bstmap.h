#ifndef _BSTMAP_H_
#define _BSTMAP_H_
#include <stdio.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
  class BstNode
  {
   public:
    K key;
    V value;
    BstNode * left;
    BstNode * right;

    BstNode(const K & k, const V & v) :
        key(k),
        value(v),
        left(NULL),
        right(NULL) {}  // default constructor
    BstNode(const K & k, const V & v, BstNode * l, BstNode * r) :
        key(k),
        value(v),
        left(l),
        right(r) {}  // nontrivial constructor
  };

  BstNode * root;

 public:
  BstMap() : root(NULL){};  // default constructor

  virtual void add(const K & key, const V & value) {
    BstNode ** current = &root;  // root of the tree
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        (*current)->value = value;
        break;
      }
    }
    *current = new BstNode(key, value, NULL, NULL);
  }  // defining add method inherited from map class. Pointer to pointer used.

  virtual void helpcopy(BstNode * curr) {
    if (curr != NULL) {
      add(curr->key, curr->value);
      helpcopy(curr->left);
      helpcopy(curr->right);
    }
  }  // helper method for copy constructor in preorder traversal

  BstMap(const BstMap<K, V> & rhs) : root(NULL) {
    BstNode * current_rhs = rhs.root;  // pointer to move through rhs BstMap
    helpcopy(current_rhs);
  }  // copy constructor

  virtual BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }  // assignment operator using std::swap

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    BstNode * curr = root;
    while (curr != NULL) {
      if (curr->key > key) {
        curr = curr->left;
      }
      else if (curr->key < key) {
        curr = curr->right;
      }
      else {
        return curr->value;
      }
    }
    throw std::invalid_argument("key not here");

  }  // defining lookup method inherited from map class.

  virtual BstNode * findmin(BstNode * curr) {
    while (curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }  // FindMin method for tree.

  virtual BstNode * helpremove(BstNode * curr, const K & key) {
    if (curr == NULL) {
      return curr;  // empty tree
    }
    else if (key < curr->key) {
      curr->left = helpremove(curr->left, key);
    }

    else if (key > curr->key) {
      curr->right = helpremove(curr->right, key);
    }

    else {
      if (curr->left == NULL && curr->right == NULL) {
        delete curr;  // no children here
        curr = NULL;
      }
      else if (curr->left == NULL) {
        // here there is one child, a right child
        BstNode * temp = curr;
        curr = curr->right;
        delete temp;
      }

      else if (curr->right == NULL) {
        // here there is one child, a left child
        BstNode * temp = curr;
        curr = curr->left;
        delete temp;
      }
      else {
        // here there are 2 children
        BstNode * temp = findmin(curr->right);
        curr->key = temp->key;
        curr->value = temp->value;
        curr->right = helpremove(curr->right, temp->key);  // perhaps change this.
      }
    }

    return curr;
  }  // helper method to remove node since remove only takes key argument.

  virtual void remove(const K & key) { helpremove(root, key); }

  virtual void helpdelete(BstNode * current) {
    if (current != NULL) {
      helpdelete(current->left);
      helpdelete(current->right);
      delete current;
    }
  }  // helper method to delete tree in postorder traversal

  virtual ~BstMap<K, V>() {
    BstNode * current = root;
    helpdelete(current);

  }  // destructor to delete entire BstMap

  virtual void printInorderhelper(BstNode * current) {
    if (current != NULL) {
      printInorderhelper(current->left);
      std::cout << current->key << "\n";
      //      std::cout << current->value << "\n";
      printInorderhelper(current->right);
    }
  }  //helper method to  print BstMap in preorder, to help with debugging.

  virtual void printInorder() { printInorderhelper(root); }  // print bstMap in preorder
};

#endif
