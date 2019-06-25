// Created by Mahmoud Shaheen on 5/8/2019.

#include <iostream>
#include "TreeType.h"

int main()
{
  TreeType<int> tree;
  
  tree.InsertItem(10);
  tree.InsertItem(9);
  tree.InsertItem(3);
  tree.InsertItem(99);
  tree.InsertItem(31);
  
  tree.PrintTree(PRE_ORDER);
  std::cout << "\n\n";
  
  tree.PrintTree(POST_ORDER);
  std::cout << "\n\n";
  
  tree.PrintTree(IN_ORDER);
  std::cout << "\n\n";
  
  tree.DeleteItem(10);
  tree.PrintTree(PRE_ORDER);
}