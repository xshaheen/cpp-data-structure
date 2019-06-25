// Created by Mahmoud Shaheen on 5/2/2019.

#include <iostream>
#include "LinkedUnsortedListType.h"

int main()
{
   LinkedUnsortedListType<int> list;
   list.InsertItem(898);
   list.InsertItem(88);
   list.InsertItem(833);
   list.PrintList();
   std::cout << std::endl;
   
   int x = 898;
   list.DeleteItem(x);
   list.PrintList();
   
   return 0;
}