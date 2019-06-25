// Created by Mahmoud Shaheen on 5/2/2019.

#include <iostream>
#include "StackType.h"

int main() 
{
   StackType<int> stack(10);
   stack.Push(9);
   stack.Push(10);
   stack.Push(8);
   stack.PrintStack();
   
   return 0;
}
