// Created by Mahmoud Shaheen on 5/6/2019.
// implementation of queue as linked structure.
// TODO: test the code 

#ifndef LINKEDQUEUETYPE_H
#define LINKEDQUEUETYPE_H

#include <iostream>

template <class ItemType>
struct NodeType{
    ItemType info;
    NodeType<ItemType> *next;
};

template <class ItemType>
class LinkedQueueType
{
private:
    NodeType<ItemType> *front;
    NodeType<ItemType> *rear;

public:
    LinkedQueueType();
    ~LinkedQueueType();
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
LinkedQueueType<ItemType>::LinkedQueueType()
{
  front = NULL;
  rear = NULL;
}

template <class ItemType>
LinkedQueueType<ItemType>::~LinkedQueueType()
// Post: Queue is empty and all elements has been de-allocated
{
  MakeEmpty();
}

template <class ItemType>
void LinkedQueueType<ItemType>::MakeEmpty()
// Post: front and rear have been reset to the empty state. and all elements has been de-allocated.
{
  // pointer to point to the item that will be deleted.
  NodeType<ItemType> *tempPtr;

  while (front != NULL){
    tempPtr = front;
    front = front->next;
    delete tempPtr;
  }
  rear = NULL;
}

template <class ItemType>
bool LinkedQueueType<ItemType>::IsEmpty() const 
// Returns true if the queue is empty; false otherwise.
{
  return (front == NULL);
}

template <class ItemType>
bool LinkedQueueType<ItemType>::IsFull() const
// Returns true if the queue is full; false otherwise.
{
  NodeType<ItemType> *test;
  
  try {
    test = new NodeType<ItemType>;
    delete test;
    return true;
  } catch (std::bad_alloc exception) {
    return false;
  }

}

template <class ItemType>
void LinkedQueueType<ItemType>::Enqueue(ItemType newItem)
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown. 
{
  if(!IsFull()){
    // prepare the new node
    NodeType<ItemType> *newNode = new NodeType<ItemType>;
    newNode->info = newItem;
    newNode->next = NULL;
    
    if (front == NULL)
      front = newNode;
    else
      rear->next = newNode;
    
    rear = newNode;
  }
}

template <class ItemType>
void LinkedQueueType<ItemType>::Dequeue(ItemType& item)
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       otherwise a EmptyQueue exception has been thrown.
{
  if (!IsEmpty()){
    // temporary pointer to delete the node
    NodeType<ItemType> *tempPtr;
    
    item = front->info;
    tempPtr = front;
    front = front->next;
    // check if you de-queue the last item in queue
    if (front == NULL)
      rear = NULL;
    delete tempPtr;
  }
    
}

template <class ItemType>
void LinkedQueueType<ItemType>::PrintQueue() const 
{
  if (!IsEmpty()){
    NodeType<ItemType> *location = front;
    while (location != NULL){
      std::cout << location->info << std::endl;
      location = location->next;
    }
  }
}


#endif //LINKEDQUEUETYPE_H
