// Created by Mahmoud Shaheen on 5/6/2019.
// implementation of linked doubly list sorted in ascending order
// TODO: test the code 

#ifndef LINKEDDOUBLYLISTTYPE_H
#define LINKEDDOUBLYLISTTYPE_H

#include <iostream>

template <class ItemType>
struct NodeType{
    ItemType info;
    NodeType<ItemType> *next;
    NodeType<ItemType> *back;
};

template <class ItemType>
class LinkedDoublyListType
{
private:
    int length;
    NodeType<ItemType> *listDataPtr;
    NodeType<ItemType> *currentPositionPtr;
   void FindItem(ItemType item, NodeType<ItemType>* &locationPtr, bool& found);
    // function: take item as a parameter and returns location and found.
    //           and will use in RetrieveItem, InsertItem, and DeleteItem 
public:
    LinkedDoublyListType();
    ~LinkedDoublyListType();
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
    void MergeLists(LinkedDoublyListType& list1, LinkedDoublyListType& list2, LinkedDoublyListType& result);
    // Merges two unsorted lists into a third unsorted list (no duplicates).
    void SplitList(ItemType item, LinkedDoublyListType& list, LinkedDoublyListType& list1, LinkedDoublyListType& list2);
    bool IsSubList(LinkedDoublyListType list1, LinkedDoublyListType list2);
    // determine if list2 (unsorted or sorted) is sub list of list1 (unsorted or sorted) and 
    // returns a Boolean indicating whether the second list is a sublist of the first.
};

template <class ItemType>
LinkedDoublyListType<ItemType>::LinkedDoublyListType()
{
  length = 0;
  listDataPtr = NULL;
}

template <class ItemType>
LinkedDoublyListType<ItemType>::~LinkedDoublyListType()
{
  MakeEmpty();
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::MakeEmpty()
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
int LinkedDoublyListType<ItemType>::LengthIs() const
{
   return length;
}

template <class ItemType>
bool LinkedDoublyListType<ItemType>::IsFull() const
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
bool LinkedDoublyListType<ItemType>::IsEmpty() const
{
  return (length == 0);
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::InsertItem(ItemType newItem)
// Pre:  list is not full
// 		 item is not in list
//		 list is sorted by key member in descending order
// Post: list is still sorted
{
   NodeType<ItemType> *newNode = new NodeType<ItemType>; // pointer to node being inserted
   newNode->info = newItem; // store newItem in the new node


   if (listDataPtr != NULL) { // if list not empty
      // find the location to insert
      NodeType<ItemType> *location;
      bool found; // just for the findItem function ignore it here.
      FindItem(newItem, location, found);

      if (newItem < location->info) {  // insert at beginning or at middle.
        // basic for middle or front insertion
         newNode->back = location->back;
         newNode->next = location;

         if (location != listDataPtr) // Case1: insert at the middle.
           (location->back)->next = newNode;
         else  // Case2: insert at the front.
           listDataPtr = newNode;
         
        location->back = newNode; // basic for middle or front insertion
      }
      else { // Case3: insert at the end.
         newNode->next = NULL;
         newNode->back = location;
         location->next = newNode;
         
      }
   }
   else { // Case4: insert into an empty list
     newNode->next = NULL;
     newNode->back = NULL;
     listDataPtr = newNode;
   }
   length++;
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::DeleteItem(ItemType& item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
// Important: this implementation will work without problems ONLY if the item to be deleted is in the list ! (precondition)
{
  // find item location
  NodeType<ItemType> *location;
  bool found;
  FindItem(item, location, found);

  if (found){
    if (location == listDataPtr) { // delete first node
      (location->next)->back = NULL; // = location->back;
      listDataPtr = listDataPtr->next;
    }
    else if (location->next == NULL){ // delete last node
      (location->back)->next = NULL; // = location->next;
    }
    else { // delete node at middle
      (location->next)->back = location->back;
      (location->back)->next = location->next; 
    }
    delete location;
    length--;
  }
  else {
    std::cout << "this item not exist." << std::endl;
  }
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
  NodeType<ItemType> *location; // needed for FindItem function
  if(!IsEmpty()){
    FindItem(item, location, found);
  }
  else
    std::cout << "List is Empty" << std::endl;
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::ResetList()
// Post: Current position has been initialized.
{
  currentPositionPtr = listDataPtr;
}

template <class ItemType>
ItemType LinkedDoublyListType<ItemType>::GetNextItem()
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
bool LinkedDoublyListType<ItemType>::IsLasItem() const
{
  return (currentPositionPtr == NULL);
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::PrintList() const
{
  NodeType<ItemType> *tempPtr = listDataPtr;

  while (tempPtr != NULL){
    std::cout << tempPtr->info << std::endl;
    tempPtr = tempPtr->next;
  }
}

template <class ItemType>
void LinkedDoublyListType<ItemType>::MergeLists(LinkedDoublyListType& list1,
                                                LinkedDoublyListType& list2,
                                                LinkedDoublyListType& result)
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
void LinkedDoublyListType<ItemType>::SplitList(ItemType item, LinkedDoublyListType& list,
                                               LinkedDoublyListType& list1,
                                               LinkedDoublyListType& list2)
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
bool LinkedDoublyListType<ItemType>::IsSubList(LinkedDoublyListType list1, LinkedDoublyListType list2)
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

template <class ItemType>
void LinkedDoublyListType<ItemType>::FindItem(ItemType item, NodeType<ItemType>* &locationPtr, bool& found)
// function: take item as a parameter and returns location and found.
//           and will use in RetrieveItem, InsertItem, and DeleteItem 
//           InsertItem and DeleteItem need location (ignore found)
//           RetrieveItem needs found (ignores location)
// Pre:  list is not empty
// Post: if found item, pointer to the node return and found be true 
//       else found be false and location point to the first element greater than.
{
  locationPtr = listDataPtr;
  ItemType currentItem;
  bool moreToSearch = true;
  found = false;
  // don't use location == NUll instead of moreToSearch 
  // because of location will reach null when insert the smallest element.
  while (!found && moreToSearch ){
    currentItem = locationPtr->info;

    if (item < currentItem)
      moreToSearch = false; // no need to continue
    else if (item == currentItem)
      found = true;
    else {
      if (locationPtr->next == NULL) // if point at last element.
        moreToSearch = false;
      else
        locationPtr = locationPtr->next;
    }
  }
}

#endif //LINKEDDOUBLYLISTTYPE_H
