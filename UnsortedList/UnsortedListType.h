// Created by Mahmoud Shaheen on 5/2/2019.
// implement Unsorted List Data Structure.
// TODO: test the code 

#include <iostream>

#ifndef DATASTRUCTURE_LINKEDLIST_LINKEDLISTTYPE_H
#define DATASTRUCTURE_LINKEDLIST_LINKEDLISTTYPE_H

template <class ItemType>
class UnsortedListType
{
private:
  int length;
  int Max_Item;
  int currentPosition;
  ItemType *info;
public:
  UnsortedListType(int max);
  ~UnsortedListType();
  void MakeEmpty();
  bool IsFull() const;
  bool IsLastItem();
  int LengthIs() const; // get the length of the list
  void RetrieveItem(ItemType& item, bool& found); // Retrieves list element whose key matches item's key (if present).
  void InsertItem(ItemType newItem); // insert newItem to list
  void DeleteItem(ItemType item); // Deletes the element whose key matches item's key
  void ResetList(); // Initializes current position for an iteration through the list
  ItemType GetNextItem(); // get the next element in the list
  void SplitLists(UnsortedListType list, ItemType item, UnsortedListType& list1, UnsortedListType& list2);
  void PrintList() const; // print all element in the list
};



template <class ItemType>
UnsortedListType<ItemType>::UnsortedListType(int max)
{
   length = 0;
   Max_Item = max;
   info = new ItemType[Max_Item];
}

template <class ItemType>
UnsortedListType<ItemType>::~UnsortedListType()
{
   delete []info;
}

template <class ItemType>
void UnsortedListType<ItemType>::MakeEmpty()
{
   length = 0;
}

template <class ItemType>
bool UnsortedListType<ItemType>::IsFull() const
{
   return (length == Max_Item);
}

template <class ItemType>
int UnsortedListType<ItemType>::LengthIs() const
{
   return length;
}

template  <class ItemType>
void UnsortedListType<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
   int location = 0;
   found = false;
   while (location < length && !found){
	  if (info[location] == item){
		 found = true;
		 item = info[location];
	  }
	  else{
		 location++;
	  }
   }
}

template <class ItemType>
void UnsortedListType<ItemType>::InsertItem(ItemType newItem)
// Pre:  list is not full, 
//		 item is not in list.
//Post:  item is in list. 
{
   if (IsFull())
	  std::cout<<"List Overflow";
   else
	  info[length++] = newItem;
}

template <class ItemType>
void UnsortedListType<ItemType>::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's
{
   // TODO: check if the element is in the list before execute the code
   int location = 0;
   while(item != info[location])
	  location++;
   // move the last element instead of this  element
   info[location] = info[--length];
}

template <class ItemType>
void UnsortedListType<ItemType>::ResetList()
// Post: Current position is prior to first element in list.
{
   currentPosition = -1;
}

template <class ItemType>
ItemType UnsortedListType<ItemType>::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
// 		 No transformer has been executed since last call.
//       currentPos is defined.
//Post:  Current position is updated to next position,
// 		 Item is a copy of element at current position. 
{
   return info[++currentPosition];
}

template <class ItemType>
bool UnsortedListType<ItemType>::IsLastItem()
{
   return (currentPosition == length - 1);
}

template <class ItemType>
void UnsortedListType<ItemType>::SplitLists(UnsortedListType list,
											ItemType item,
											UnsortedListType &list1,
											UnsortedListType &list2)
// Pre:  list has been initialised and is not empty
// Post: list1 contains all the items of list whose keys are less
//       than or equal to item's key;
//       list2 contains all the items of list whose keys are greater
//       than item's key.
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
void UnsortedListType<ItemType>::PrintList() const
// Pre: list is not empty.
{
   for (int index= 0; index < LengthIs(); ++index) {
	  std::cout << info[index] << std::endl;
   }
}

#endif // DATASTRUCTURE_LINKEDLIST_LINKEDLISTTYPE_H