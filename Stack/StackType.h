// Created by Mahmoud Shaheen on 5/2/2019.
// implement stack as dynamic array allocation
// TODO: test the code 

#ifndef DATASTRUCTURE_STACK_STACKTYPE_H
#define DATASTRUCTURE_STACK_STACKTYPE_H

template <class ItemType>
class StackType
{
private:
  int top;
  int Max_Item;
  ItemType *items;

public:
  StackType(int max);
  ~StackType();
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  void Push(ItemType newItem);
  void Pop(ItemType& item);
  void PrintStack();
};


template <class ItemType>
StackType<ItemType>::StackType(int max)
{
   Max_Item = max;
   top = -1;
   items = new ItemType[Max_Item];
}

template <class ItemType>
StackType<ItemType>::~StackType()
{
   delete []items;
}

template <class ItemType>
void StackType<ItemType>::MakeEmpty()
{
   top = -1;
}

template <class ItemType>
bool StackType<ItemType>::IsEmpty() const
{
   return (top == -1);
}

template <class ItemType>
bool StackType<ItemType>::IsFull() const
{
   return (top == Max_Item - 1);
}

template <class ItemType>
void StackType<ItemType>::Push(ItemType newItem)
{
   if (!IsFull()){
	  ++top;
	  items[top] = newItem;
   }
}

template <class ItemType>
void StackType<ItemType>::Pop(ItemType &item)
{
   if (!IsEmpty()){
	  item = item[top];
	  --top;
   }
}

template <class ItemType>
void StackType<ItemType>::PrintStack()
{
   if (!IsEmpty()){
	  for (int I = 0; I <= top; ++I) {
		 std::cout << "Item[" << I << "] = " << items[I] << std::endl;
	  }
   }

}

#endif // DATASTRUCTURE_STACK_STACKTYPE_H