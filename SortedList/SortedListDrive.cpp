// Created by Mahmoud Shaheen on 5/2/2019.
// implement Sorted List Data Structure


#include "SortedListType.h"

int main()
{
   SortedListType<int> list(12);
   std::cout << "list is full? = " << list.IsFull() << std::endl;
   
   list.InsertItem(89);
   list.InsertItem(80);
   list.InsertItem(33);
   list.InsertItem(98);
   list.PrintList();
   
   std::cout << std::endl;
   
   int x = 89;
   list.DeleteItem(x);
   list.PrintList();
   return 0;
}
