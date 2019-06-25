// Created by Mahmoud Shaheen on 5/2/2019.
// Implementation file for linked StackType
// TODO: test the code 

#ifndef DATASTRUCTURE_LINKEDSTACK_LINKEDSTACKTYPE_H
#define DATASTRUCTURE_LINKEDSTACK_LINKEDSTACKTYPE_H

#include <new>

template <class ItemType>
struct NodeType{
  ItemType info;
  NodeType<ItemType> *next;
};

template <class ItemType>
class LinkedStackType {
private:
  NodeType<ItemType> *topPtr;
  
public:
  LinkedStackType();
  ~LinkedStackType();
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const ;
  ItemType Peek();
  void Push(ItemType newItem);
  void Pop(ItemType& item);
  void PrintStack();
};

template <class ItemType>
LinkedStackType<ItemType>::LinkedStackType() 
{
  topPtr = NULL;
}

template <class ItemType>
LinkedStackType<ItemType>::~LinkedStackType()
// Post: stack is empty; all items have been de-allocated.
{
  MakeEmpty();
}

template <class ItemType>
void LinkedStackType<ItemType>::MakeEmpty()
// Post: stack is empty and all element has been de-allocated
{
  // temporary pointer to delete the nodes
  NodeType<ItemType> *tempPtr;
  
  while (topPtr != NULL){
    tempPtr = topPtr;
    topPtr = topPtr->next;
    delete tempPtr;
  }
  
}

template <class ItemType>
bool LinkedStackType<ItemType>::IsEmpty() const 
{
  return (topPtr == NULL);
}

template <class ItemType>
bool LinkedStackType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise
{
  NodeType<ItemType> *location;
  try
  {
    location = new NodeType<ItemType>;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template <class ItemType>
ItemType LinkedStackType<ItemType>::Peek()
{
  if (IsEmpty())
    std::cout << "Stack is Empty" << std::endl;
  else
    return topPtr->info;
}

template <class ItemType>
void LinkedStackType<ItemType>::Push(ItemType newItem)
// Adds newItem to the top of the stack.
// Stack is bounded by size of memory.
// Pre:  Stack has been initialized.
// Post: If stack is full, FullStack exception is thrown;
//       else newItem is at the top of the stack.
{
  if (IsFull())
    std::cout << "The stack is full. No available memory" << std::endl;
  else{
    // create pointer to new node
    NodeType<ItemType> *locationPtr = new NodeType<ItemType>;
    // assign info to the newItem
    locationPtr->info = newItem;
    // make nextPtr point to the old top item
    locationPtr->next = topPtr;
    // make topPtr point to the new node
    topPtr = locationPtr;

    delete locationPtr;
  }
}

template <class ItemType>
void LinkedStackType<ItemType>::Pop(ItemType& item)
// Removes top item from Stack and returns it in item.
// Pre:  Stack has been initialized.
// Post: If stack is empty, EmptyStack exception is thrown;
//       else top element has been removed. and item has a copy of it
{
  if (IsEmpty())
    std::cout << "The stack is Empty!" << std::endl;
  else{
    // temporary pointer to can delete the pop item
    NodeType<ItemType> *tempPtr = topPtr;
    // return the top item
    item = topPtr->info;
    // make topPtr point to the next
    topPtr = topPtr->next;
    delete tempPtr;
  }
}

template <class ItemType>
void LinkedStackType<ItemType>::PrintStack()
{
  // temporary pointer to print
  NodeType<ItemType> *tempPtr = topPtr;
  
  while(tempPtr != NULL){
    std::cout << tempPtr->info << std::endl;
    tempPtr = tempPtr->next;
  }
}


#endif //DATASTRUCTURE_LINKEDSTACK_LINKEDSTACKTYPE_H
