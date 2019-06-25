// Created by Mahnmoud Shaheen on 5/5/2019.

#include "LinkedSortedListType.h"

int main()
{
  LinkedSortedListType<int> list, list2, result;
  list.InsertItem(37);
  list.InsertItem(33);
  list.InsertItem(12);
  list.PrintList();
  
  std::cout << std::endl;
  
  int x = 33;
  list.DeleteItem(x);
  
  list.InsertItem(12);
  list.InsertItem(10);
  list.InsertItem(99);
  list.PrintList();
  
  return 0;
}
