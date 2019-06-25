// Created by Mahmoud Shaheen on 5/2/2019.
// implement Sorted List Data Structure.
// TODO: test the code 

#include <iostream>

#ifndef DATASTRUCTURE_SORTEDLIST_SORTEDLISTTYPE_H
#define DATASTRUCTURE_SORTEDLIST_SORTEDLISTTYPE_H

template <class ItemType>
class SortedListType
{
private:
  ItemType *info;
  int length;
  int maxList;
  int currentPosition;
public:
  SortedListType(int max);
  ~SortedListType();
  void MakeEmpty();
  bool IsFull() const;
  int LengthIs() const;
  void InsertItem(ItemType newItem);// add item to list.
  void DeleteItem(ItemType& item);// delete item whose key matches item`s key
  void RetrieveItemLinear(ItemType& item, bool& found);// retrieve list element whose key matches item`s key (if present)
  void RetrieveItemBinary(ItemType& item, bool& found);// retrieve list element whose key matches item`s key (if present)
  void RestList();// Initializes current position for an iteration through the list
  bool IsLastItem() const;
  ItemType GetNextItem();
  void PrintList() const;
  void MergeLists(SortedListType& list1, SortedListType& list2, SortedListType& result);
};



template <class ItemType>
SortedListType<ItemType>::SortedListType(int max)
{
   maxList = max;
   info = new ItemType[maxList];
   length = 0;
}

template <class ItemType>
SortedListType<ItemType>::~SortedListType()
{
   delete []info;
}

template <class ItemType>
void SortedListType<ItemType>::MakeEmpty()
{
   length = 0;
}

template <class ItemType>
bool SortedListType<ItemType>::IsFull() const
{
   return (length == maxList);
}

template <class ItemType>
int SortedListType<ItemType>::LengthIs() const
{
   return length;
}

template <class ItemType>
void SortedListType<ItemType>::InsertItem(ItemType newItem)
// Pre:  list is not full
// 		 item is not in list
//		 list is sorted by key member in descending order
// Post: list is still sorted
{
   if (IsFull())
      std::cout << "List Overflow." << std::endl;
   else{
      // find place to insert
      int location = 0;
      while (location < length ) {
        if (newItem < info[location]) {
          break; // the location has been founded
        } else
          location++;
      }
     // move all elements after one place forward then insert
     for (int index = length; index > location; index--)
       info[index] = info[index - 1];

     // now you can insert
     info[location] = newItem;
     length++;
      
   }
}

template <class ItemType>
void SortedListType<ItemType>::DeleteItem(ItemType &item)
// Pre:  Key member of item has been initialized 
//		 There is only one element in the list which has a key matches item`s key
// 		 list is sorted by key member
// Post: list is still Sorted
{
   // find item location
   int location = 0;
   while (item != info[location])
		 location++;
   
   // move all elements after one place backward
   for (int index = location; index < length; ++index)
      info[index] = info[index + 1];
   
   length--;
}

template <class ItemType>
void SortedListType<ItemType>::RetrieveItemLinear(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
   int location = 0;
   found = false;
   while(!found && location < length){
      if (item == info[location]) {
		 found = true;
		 item = info[location];
	  }
	  else if (item > info[location])
		 location = length; // no reason to continue terminate the loop
	  else
		 location++;
   }
}

template <class ItemType>
void SortedListType<ItemType>::RetrieveItemBinary(ItemType &item, bool &found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
   int midPoint;
   int first = 0;
   int last = length - 1;
   
   found = false;
   while (!found && (first <= last)){
     midPoint = (first + last) / 2;
     
     if (item == info[midPoint]){
       found = true;
       item = info[midPoint];
     }
     else if (item < info[midPoint])
       last = midPoint - 1;
     else
       first = midPoint + 1;
   }
      
}

template <class ItemType>
void SortedListType<ItemType>::RestList()
// Post: Current position is prior to first element in list.
{
   currentPosition = -1;
}

template <class ItemType>
bool SortedListType<ItemType>::IsLastItem() const
{
   return (currentPosition == length - 1);
}

template <class ItemType>
ItemType SortedListType<ItemType>::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
// 	 No transformer has been executed since last call.
//       currentPos is defined.
//Post:  Current position is updated to next position,
//       return a copy of element at current position. 
{
  return info[++currentPosition];
}

template <class ItemType>
void SortedListType<ItemType>::PrintList() const 
// Pre: list is not Empty
{
   for (int index = 0; index < length; ++index) {
      std::cout << info[index] << std::endl;
   }
}

template <class ItemType>
void SortedListType<ItemType>::MergeLists(SortedListType& list1, SortedListType& list2, SortedListType& result)
{
  int i;
  int length = list1.LengthIs();
  list1.RestList();
  for(i = 0; i < length; i++) {
    result.InsertItem(list1.GetNextItem());
  }

  length = list2.LengthIs();
  list2.ResetList();
  
  for(i = 0; i < length; i++) {
    result.InsertItem(list2.GetNextItem());
  }
  
}

#endif // DATASTRUCTURE_SORTEDLIST_SORTEDLISTTYPE_H