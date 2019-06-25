// Created by Mahmoud Shaheen on 5/2/2019.
// This file contains the linked Unsorted List implementation 
// TODO: test the code 

#ifndef DATASTRUCTURE_LINKEDUNSORTEDLIST_LINKEDUNSORTEDLISTTYPE_H
#define DATASTRUCTURE_LINKEDUNSORTEDLIST_LINKEDUNSORTEDLISTTYPE_H

#include <iostream>

template <class ItemType>
struct NodeType {
  ItemType info;
  NodeType<ItemType> *next;
};

template <class ItemType>
class LinkedUnsortedListType
{
private:
  int length;
  NodeType<ItemType> *CurrentPositionPtr;
  NodeType<ItemType> *ListDataPtr; 

public:
  LinkedUnsortedListType();
  ~LinkedUnsortedListType();
  void MakeEmpty(); //Returns the list to the empty state.
  bool IsEmpty() const;
  bool IsFull() const;
  int LengthIs() const; // Determines the number of elements in list.
  void RetrieveItem(ItemType& item, bool& found); // Retrieves list element whose key matches item's key (if present).
  void InsertItem(ItemType newItem);
  void DeleteItem(ItemType& item); // Deletes the element whose key matches item's key.
  void ResetList(); // Initializes current position for an iteration through the list.
  bool IsLastItem() const;
  ItemType GetNextItem(); // Gets the next element in list.
  void PrintList();
  void MergeLists(LinkedUnsortedListType& list1, LinkedUnsortedListType& list2, LinkedUnsortedListType& result);
  // Merges two unsorted lists into a third unsorted list (no duplicates).
  void SplitList(ItemType item, LinkedUnsortedListType& list, LinkedUnsortedListType& list1, LinkedUnsortedListType& list2);
};

template <class ItemType>
LinkedUnsortedListType<ItemType>::LinkedUnsortedListType()
{
  length = 0;
  ListDataPtr = NULL;
}

template <class ItemType>
LinkedUnsortedListType<ItemType>::~LinkedUnsortedListType()
// Post: List is empty; all items have been de-allocated.
{
  MakeEmpty();
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::MakeEmpty()
// Post: List is empty; all items have been de-allocated.
{
    // temporary pointer to hold item to delete
    NodeType<ItemType> *tempPtr;
    
    while (ListDataPtr != NULL){
        tempPtr = ListDataPtr;
        ListDataPtr = ListDataPtr->next;
        delete tempPtr;
    }
    length = 0;
}

template <class ItemType>
bool LinkedUnsortedListType<ItemType>::IsEmpty() const
{
  return (length == 0);
}

template <class ItemType>
bool LinkedUnsortedListType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
{
    NodeType<ItemType>* location;
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
int LinkedUnsortedListType<ItemType>::LengthIs() const
{
  return length;
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
    // temporary pointer 
    NodeType<ItemType> *locationPtr = ListDataPtr;

    found = false;
    while((locationPtr != NULL) && !found){
        if (item == locationPtr->info){
            found = true;
            item = locationPtr->info;
        }
        else{
            locationPtr = locationPtr->next;
        }
    }
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::InsertItem(ItemType newItem)
{
  // declare a temporary pointer to new node
  NodeType<ItemType> *tempPtr = new NodeType<ItemType>;
  // store newItem in the node
  tempPtr->info = newItem;
  // store address to the next node
  tempPtr->next = ListDataPtr;
  // store address of new node into external pointer
  ListDataPtr = tempPtr;
  // increment the address of the list
  length++;
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::DeleteItem(ItemType& item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
// Important: this implementation will work without problems ONLY if the item to be deleted is in the list ! (precondition)
// TODO: improve the algorithm to work correctly if the item is not in the list.
{
    NodeType<ItemType> *locationPtr = ListDataPtr;
    NodeType<ItemType> *tempLocationPtr;
    
    if (locationPtr->info == item){
        tempLocationPtr = locationPtr;
        ListDataPtr = ListDataPtr->next; // delete the first node
    } else {
        // find the node
        while (item != (locationPtr->next)->info) // compare one item ahead after the first
            locationPtr = locationPtr->next;
        
        // delete the locationPtr->next
        tempLocationPtr = locationPtr->next;
        locationPtr->next = (locationPtr->next)->next;
    }
    delete tempLocationPtr;
    length--;
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::ResetList()
// Post: Current position has been initialized.
{
  CurrentPositionPtr = NULL;
}

template <class ItemType>
bool LinkedUnsortedListType<ItemType>::IsLastItem() const
{
  return (CurrentPositionPtr == NULL);
}

template <class ItemType>
ItemType LinkedUnsortedListType<ItemType>::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       currentPos is defined.
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
{
    ItemType item;
    
    if (CurrentPositionPtr == NULL) // if current position out of the list or at the end
        CurrentPositionPtr = ListDataPtr;

    // you consider the current position as the next 
    // because when reach the last element (NULL) do not do ->next
    item = CurrentPositionPtr->info;
    CurrentPositionPtr = CurrentPositionPtr->next;
    return item;
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::PrintList() 
{
    NodeType<ItemType> *tempPtr = ListDataPtr;
    while (tempPtr != NULL){
        std::cout << tempPtr->info << std::endl;
        tempPtr = tempPtr->next;
    }
}

template <class ItemType>
void LinkedUnsortedListType<ItemType>::MergeLists(LinkedUnsortedListType& list1, LinkedUnsortedListType& list2, LinkedUnsortedListType& result)
{
    // some variables
    ItemType currentItem;
    bool found;
    
    // reset current position pointer to the beginning of the lists
    list1.ResetList();
    list2.ResetList();
    // Make sure the result list is empty
    result.MakeEmpty();

    
    while ( !list1.IsLastItem() ) {
      currentItem = list1.GetNextItem();
        if ( !result.IsFull() )
            result.InsertItem(currentItem);
    }
    
    while ( !list2.IsLastItem() ) {
      currentItem = list2.GetNextItem();
        
        // Make sure no duplicates
        list1.RetrieveItem(currentItem, found);
        if ( !found )
            if ( !result.IsFull() )
                result.InsertItem(currentItem);
    }
}
template <class ItemType>
void LinkedUnsortedListType<ItemType>::SplitList(ItemType item, LinkedUnsortedListType& list, LinkedUnsortedListType& list1, LinkedUnsortedListType& list2)
// Pre:  list has been initialised and is not empty
// Post: list1 contains all the items of list whose keys are less
//       than os equal to item's key;
//       list2 contains all the items of list whose keys are greater
//       than item'; key.
{
    // variable to hold item of the list
    ItemType currentItem;
    // Make sure the two other lists is empty
    list1.MakeEmpty();
    list2.MakeEmpty();
    // start at the beginning of the list
    list.ResetList();
    while(!list.IsLastItem()){
        currentItem = list.GetNextItem();
        if (currentItem >= item)
            list1.InsertItem(currentItem);
        else
            list2.InsertItem(currentItem);
    }
}

template <class ItemType>
NodeType<ItemType>* LinkedUnsortedListType<ItemType>::MinimumNode()
{
  NodeType<ItemType *location; // traveling pointer
  NodeType<ItemType> *miniLocation; // mini node pointer
  ItemType minItem;

  // suppose that the first element is the mini
  minItem = listData->info;
  miniLocation = listData;
  
  location = listData;
  
  // travel through the list and pick the minimum element 
  while (location->next != NULL) {
    location = location->next;
    
    if (location->info < minItem) {
      minItem = location->info;
      miniLocation = location;
    }
  }
  return miniLocation;
}



#endif // DATASTRUCTURE_LINKEDUNSORTEDLIST_LINKEDUNSORTEDLISTTYPE_H
