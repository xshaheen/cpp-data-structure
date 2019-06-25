// Created by Mahmoud Shaheen on 5/2/2019.

#include <iostream>
#include "LinkedStackType.h"

int main()
{
   LinkedStackType<int> stack;
   stack.Push(33);
   stack.Push(2);
   stack.Push(3);
   stack.Push(7);
   stack.PrintStack();
   
   int popItem;
   stack.Pop(popItem);
   
   stack.PrintStack();
   
   return 0;
}


