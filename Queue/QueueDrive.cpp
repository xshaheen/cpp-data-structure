// Created by Mahmoud Shaheen on 5/2/2019.

#include <iostream>
#include "QueueType.h"

int main()
{
   QueueType<int> queue(5);
   queue.Enqueue(80);
   queue.Enqueue(10);
   queue.Enqueue(50);
   queue.Enqueue(5);
   queue.Enqueue(1);
   queue.PrintQueue();

   return 0;
}
