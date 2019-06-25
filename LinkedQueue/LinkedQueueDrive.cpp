// Created by Mahmoud on 5/6/2019.
// test drive

#include <iostream>
#include "LinkedQueueType.h"

using namespace std;
int main()
{
  LinkedQueueType<int> list;
  
  list.Enqueue(33);
  list.Enqueue(34);
  list.Enqueue(44);
  list.PrintQueue();

  int x;
  
  list.Dequeue(x);
  list.PrintQueue();
  
}

