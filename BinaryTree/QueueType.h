// Created by Mahmoud Shaheen on 5/2/2019.
// Implement queue as circular structure
// TODO: test the code 

#ifndef DATASTRUCTURE_QUEUE_QUEUETYPE_H
#define DATASTRUCTURE_QUEUE_QUEUETYPE_H

template <class ItemType>
class QueueType
{
private:
  int front;
  int rear;
  int maxQueue;
  ItemType *items;
  
public:
  QueueType();
  QueueType(int max);
  ~QueueType();
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  void Enqueue(ItemType newItem);
  // Function: Adds newItem to the rear of the queue.
  // Post: If (queue is full) FullQueue exception is thrown
  //       else newItem is at rear of queue.
  void Dequeue(ItemType& item);
  // Function: Removes front item from the queue and returns it in item.
  // Post: If (queue is empty) EmptyQueue exception is thrown
  //       and item is undefined
  //       else front element has been removed from queue and
  //       item is a copy of removed element.
  void PrintQueue() const;
};

template <class ItemType>
QueueType<ItemType>::QueueType()
{
   maxQueue = 10;
   items = new ItemType[maxQueue];
   front = maxQueue - 1;
   rear = maxQueue - 1;
}
template <class ItemType>
QueueType<ItemType>::QueueType(int max)
{
   maxQueue = max;
   items = new ItemType[maxQueue];
   front = maxQueue - 1;
   rear = maxQueue - 1;
}

template <class ItemType>
QueueType<ItemType>::~QueueType()
{
   delete [] items;
}

template <class ItemType>
void QueueType<ItemType>::MakeEmpty()
// Post: front and rear have been reset to the empty state.
{
   front = maxQueue - 1;
   rear = maxQueue - 1;
}

template <class ItemType>
bool QueueType<ItemType>::IsEmpty() const 
// Returns true if the queue is empty; false otherwise.
{
   return (front == rear);
}

template <class ItemType>
bool QueueType<ItemType>::IsFull() const 
// Returns true if the queue is full; false otherwise.
{
   return ((rear + 1) % maxQueue == front);
}

template <class ItemType>
void QueueType<ItemType>::Enqueue(ItemType newItem)
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown. 
{
   if (IsFull())
      std::cout << "Queue Overflow." << std::endl;
   else {
	  rear = (rear + 1) % maxQueue;
	  items[rear] = newItem;
   }
}

template <class ItemType>
void QueueType<ItemType>::Dequeue(ItemType& Item)
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{
   if (IsEmpty())
	  std::cout << "Queue Underflow." << std::endl;
   else {
   front = (front + 1) % maxQueue;
   items = items[front];
   }
}

template <class ItemType>
void QueueType<ItemType>::PrintQueue() const 
{
   if (!IsEmpty()){
	  std::cout << "Front:"<< "\t";
	  for (int index = (front + 1) % maxQueue; index <= rear; index = (index + 1) %maxQueue) {
		 std::cout << items[index] << "\t";
	  }
   }
}

#endif // DATASTRUCTURE_QUEUE_QUEUETYPE_H