// Created by Mahmoud Shaheen on 5/5/2019.
// Implimentation 
// TODO: test the code 

#ifndef DATASTRUCTURE_LINKEDSORTEDLIST_H
#define DATASTRUCTURE_LINKEDSORTEDLIST_H

#include <iostream>

template <class ItemType>
struct NodeType {
    ItemType info;
    NodeType<ItemType> *next;
};

template <class ItemType>
class LinkedSortedListType
{
private:
    int length;
    NodeType<ItemType> *listDataPtr;
    NodeType<ItemType> *currentPositionPtr;
public:
    LinkedSortedListType();
    ~LinkedSortedListType();
    void MakeEmpty(); // Returns the list to the empty state.
    int LengthIs() const; // Determines the number of elements in list.
    bool IsFull() const;
    bool IsEmpty() const;
    void InsertItem(ItemType newItem);
    void DeleteItem(ItemType& item); // delete item whose key matches item's key
    void RetrieveItem(ItemType& item, bool& found); // Retrieves list element whose key matches item's key (if present).
    void ResetList(); // Initializes current position for an iteration through the list.
    ItemType GetNextItem(); // Gets the next element in list.
    bool IsLasItem() const;
    void PrintList() const;
    void MergeLists(LinkedSortedListType& list1, LinkedSortedListType& list2, LinkedSortedListType& result);
    // Merges two unsorted lists into a third unsorted list (no duplicates).
    void SplitList(ItemType item, LinkedSortedListType& list, LinkedSortedListType& list1, LinkedSortedListType& list2);
    bool IsSubList(LinkedSortedListType list1, LinkedSortedListType list2);
    // determine if list2 (unsorted or sorted) is sub list of list1 (unsorted or sorted) and 
    // returns a Boolean indicating whether the second list is a sublist of the first.
};

template <class ItemType>
LinkedSortedListType<ItemType>::LinkedSortedListType()
{
    length = 0;
    listDataPtr = NULL;
}

template <class ItemType>
LinkedSortedListType<ItemType>::~LinkedSortedListType()
{
    MakeEmpty();
}

template <class ItemType>
void LinkedSortedListType<ItemType>::MakeEmpty()
// Post: list is Empty and All element has been de-allocated.
{
    // temporary pointer to point to the data that will be deleted
    NodeType<ItemType> *tempPtr;

    while (listDataPtr != NULL){
        tempPtr = listDataPtr;
        listDataPtr = listDataPtr->next;
        delete tempPtr;
    }
}

template <class ItemType>
int LinkedSortedListType<ItemType>::LengthIs() const
{
    return length;
}

template <class ItemType>
bool LinkedSortedListType<ItemType>::IsFull() const
// return true if there is no room for another ItemType
// on the free store, false otherwise.
{
    NodeType<ItemType> *test;

    try {
        test = new NodeType<ItemType>;
        delete test;
        return false;
    } 
    catch (std::bad_alloc exception){
        return true;
    }
}

template <class ItemType>
bool LinkedSortedListType<ItemType>::IsEmpty() const
{
    return (length == 0);
}

template <class ItemType>
void LinkedSortedListType<ItemType>::InsertItem(ItemType newItem)
// Pre:  list is not full
// 		 item is not in list
//		 list is sorted by key member in descending order
// Post: list is still sorted
{
    // pointer to insert
    NodeType<ItemType>* newNode = new NodeType<ItemType>;  	// pointer to node being inserted
    NodeType<ItemType>* previousLoc = NULL;  	// trailing pointer.
    NodeType<ItemType>* location = listDataPtr; 	// traveling pointer

    // store newItem in the new node
    newNode->info = newItem;
    
    // Find insertion point.
    while (location != NULL){
        if (newItem < location->info){
            previousLoc = location; // we must keep track of previous location
            location = location->next;
        } else
            break;
    }
    
    // insert newNode in list
    if (previousLoc == NULL){ // insert as first
        listDataPtr = newNode;
        newNode->next = location;
    } else{
        previousLoc->next = newNode;
        newNode->next = location;
    }
    
    length++;
}

template <class ItemType>
void LinkedSortedListType<ItemType>::DeleteItem(ItemType& item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
// Important: this implementation will work without problems ONLY if the item to be deleted is in the list ! (precondition)
// TODO: improve the algorithm to work correctly if the item is not in the list.
{
    // temporary pointer to point to node that will be deleted
    NodeType<ItemType> *location = listDataPtr; // traveling pointer
    NodeType<ItemType> *tempLocation; // 
    
    if (item == listDataPtr->info){// if the item is first
        // delete first node
        tempLocation = listDataPtr;
        listDataPtr = listDataPtr->next;
    } else{
        // find the item
        while ((location->next)->next != NULL){ // search from the second element.
            if (item == (location->next)->info){
                // delete node at location->next
                tempLocation = location->next;
                location->next = (location->next)->next;
            }
        }
    }
    delete tempLocation;
    length--;
}

template <class ItemType>
void LinkedSortedListType<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
    NodeType<ItemType> *location = listDataPtr; // traveling pointer
    
    found = false;
    while (!found && location != NULL){
        if (item == location->info){
            found = true;
            item = location->info;
        } else if (item < location->info){
            location = location->next;
        } else{
            location = NULL; // no reason to continue
        }
    }
}

template <class ItemType>
void LinkedSortedListType<ItemType>::ResetList()
// Post: Current position has been initialized.
{
    currentPositionPtr = listDataPtr;
}

template <class ItemType>
ItemType LinkedSortedListType<ItemType>::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       currentPos is defined.
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
{
  ItemType item;
  
  if (currentPositionPtr == NULL) // if current position out of the list or at the end
    currentPositionPtr = listDataPtr;
  // you consider the current position as the next 
  // because when reach the last element (NULL) do not do ->next
  item = currentPositionPtr->info;
  currentPositionPtr = currentPositionPtr->next;
  return item;
}

template <class ItemType>
bool LinkedSortedListType<ItemType>::IsLasItem() const
{
  return (currentPositionPtr == NULL);
}

template <class ItemType>
void LinkedSortedListType<ItemType>::PrintList() const
{
  NodeType<ItemType> *tempPtr = listDataPtr;
  
  while (tempPtr != NULL){
    std::cout << tempPtr->info << std::endl;
    tempPtr = tempPtr->next;
  }
}

template <class ItemType>
void LinkedSortedListType<ItemType>::MergeLists(LinkedSortedListType& list1,
                                                LinkedSortedListType& list2,
                                                LinkedSortedListType& result)
{
  // some variables
  ItemType currentItem;
  bool found;
  // reset current position pointer to null
  list1.ResetList();
  list2.ResetList();
  // make sure that list is empty
  result.MakeEmpty();
  
  while (!list1.IsLasItem()) {
    currentItem = list1.GetNextItem();
    result.InsertItem(currentItem);
  }
  while (!list2.IsLasItem()){
    currentItem = list2.GetNextItem();
    // make sure no duplicates
    list1.RetrieveItem(currentItem , found);
    if (!found && !result.IsFull())
      result.InsertItem(currentItem);
  }
}

template <class ItemType>
void LinkedSortedListType<ItemType>::SplitList(ItemType item, LinkedSortedListType& list, 
                                                              LinkedSortedListType& list1, 
                                                              LinkedSortedListType& list2)
// Pre:  list has been initialised and is not empty
// Post: list1 contains all the items of list whose keys are less
//       than os equal to item's key;
//       list2 contains all the items of list whose keys are greater
//                                                    
{
  // variable to hold item of the list
  ItemType currentItem;
  // make sure the two list is empty
  list1.MakeEmpty();
  list2.MakeEmpty();
  // start at the beginning of the list
  list.ResetList();
  while ( !list.IsLasItem() ){
    currentItem = list.currentPositionPtr->info;
    if (currentItem >= item)
      list1.InsertItem(currentItem);
    else
      list2.InsertItem(currentItem);
  }
}

template <class ItemType>
bool LinkedSortedListType<ItemType>::IsSubList(LinkedSortedListType list1, LinkedSortedListType list2)
{
  ItemType item;
  bool isSubList = true;
  // initialize the current position to beginning of the list
  list1.ResetList();
  list2.ResetList();
  
  while (!list2.IsLasItem() && isSubList){
    item = list2.GetNextItem();
    list1.RetrieveItem(item, isSubList);
  }
  return isSubList;
}

#endif //DATASTRUCTURE_LINKEDSORTEDLIST_H
