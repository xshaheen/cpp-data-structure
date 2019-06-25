// Created by Mahmoud Shaheen on 5/2/2019.

#include <iostream>
#include "UnsortedListType.h"

int main()
{
   UnsortedListType<int> list(6);

   list.InsertItem(11);
   list.InsertItem(1);
   list.InsertItem(165);
   list.InsertItem(16);
   list.PrintList();

   std::cout << std::endl;
   list.DeleteItem(1);
   list.PrintList();

}
