// Created by Mahmoud Shaheen on 5/7/2019.
// Test Drive

#include <iostream>
#include "LinkedDoublyListType.h"

int main()
{
  LinkedDoublyListType<int> list;
  list.InsertItem(8);
  list.InsertItem(7);
  list.InsertItem(55);
  list.InsertItem(22);
  list.InsertItem(17);
  list.PrintList();
  
  std::cout << "\n\n";
  
  int x = 55;
  list.DeleteItem(x);
  x = 7;
  list.DeleteItem(x);
  x = 17;
  list.DeleteItem(x);
  list.PrintList();

  return 0;
}

