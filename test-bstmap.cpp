#include <stdio.h>

#include <iostream>

#include "bstmap.h"
#include "map.h"

int main() {
  std::cout << "test code now with bstmap1 <int,int>"
            << "\n";

  //create a bstmap of type <int,int>
  BstMap<int, int> * m1 = new BstMap<int, int>();
  //create a bstmap of type <string,int>
  // BstMap<std::string, int> * m2 = new BstMap<std::string, int>();

  // test add method for m1
  m1->add(2, 3);
  m1->add(2, 5);

  m1->add(1, 4);
  std::cout << "add 1"
            << "\n";
  m1->printInorder();
  m1->add(1, 9);
  std::cout << "add 1"
            << "\n";
  m1->printInorder();

  m1->add(4, 7);
  m1->add(8, 3);
  m1->add(5, 2);

  std::cout << "printout tree in in order"
            << "\n";
  m1->printInorder();

  // test lookup method to check values added to tree.
  std::cout << "printout lookup values"
            << "\n";
  std::cout << m1->lookup(2) << "\n";
  std::cout << m1->lookup(1) << "\n";
  std::cout << m1->lookup(10) << "\n";
  std::cout << m1->lookup(4) << "\n";
  std::cout << m1->lookup(8) << "\n";
  std::cout << m1->lookup(5) << "\n";

  //test remove method
  m1->remove(5);
  std::cout << "tree inorder after removal of 5"
            << "\n";
  m1->printInorder();

  m1->remove(4);
  std::cout << "tree in order after removal of 4"
            << "\n";
  m1->printInorder();

  return EXIT_SUCCESS;
}
