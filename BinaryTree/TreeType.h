// Created by Mahmoud Shaheen on 5/8/2019.
// Implementation of binary tree.
// TODO: test code well

#ifndef TREETYPE_H
#define TREETYPE_H


#include <iostream>
#include "QueueType.h"

template <class ItemType>
struct TreeNode{
   ItemType info;
   TreeNode<ItemType> *left;
   TreeNode<ItemType> *right;
};

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

template <class ItemType>
class TreeType
{
public:
   TreeType();
   ~TreeType();
   TreeType(const TreeType<ItemType>& originalTree); // copy constructor
   void MakeEmpty(); // Returns the list to the empty state.
   bool IsEmpty() const;
   bool IsFull() const;
   int NumberOfNodes() const; // Determines the number of elements in tree.
   void RetrieveItem(ItemType&, bool& found);
   void InsertItem(ItemType newItem);
   void DeleteItem(ItemType item); // delete item whose key matches item's key
   void ResetTree(OrderType order);
   // for an iteration through the tree and the user is allowed to specify the tree traversal order
   void GetNextItem(ItemType& item, OrderType order, bool& finished); // Gets the next element in list.
   void PrintTree(OrderType order) const;
private:
   TreeNode<ItemType> *root;
   // needs for ResetTree function
   QueueType<ItemType> preQue;
   QueueType<ItemType> inQue;
   QueueType<ItemType> postQue;
};


template <class ItemType>
TreeType<ItemType>::TreeType()
{
  root = NULL;
}

template <class ItemType>
TreeType<ItemType>::TreeType(const TreeType<ItemType>& originalTree)
// function: make the new list a copy from tree.
{
  CopyTree(root, originalTree);
}

template <class ItemType>
void CopyTree(TreeNode<ItemType> *copy, TreeNode<ItemType> *originalTree)
{
  if(originalTree == NULL) // base case
    copy = NULL;
  else {
    copy = new TreeNode<ItemType>;
    // pre-order
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

template <class ItemType>
TreeType<ItemType>::~TreeType()
// Post: tree is Empty and All element has been de-allocated.
{
  Destroy(root);
}

template <class ItemType>
void TreeType<ItemType>::MakeEmpty()
// Post: list is Empty and All element has been de-allocated.
{
  Destroy(root);
}
template <class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
{ // Delete the tree in a "bottom-up" fashion postOrder traversal is appropriate for that.
  if(tree != NULL) {
   Destroy(tree->left);
   Destroy(tree->right);
   delete tree;
 }
} 


template <class ItemType>
bool TreeType<ItemType>::IsEmpty() const
{
  return (root == NULL);
}

template <class ItemType>
bool TreeType<ItemType>::IsFull() const
// return true if there is no room for another ItemType
// on the free store, false otherwise.
{
  TreeNode<ItemType> *tempNode;

  try {
    tempNode = new TreeNode<ItemType>;
    delete tempNode;
    return false;
  }
  catch (std::bad_alloc exception) {
    return true;
  }

}

template <class ItemType>
int TreeType<ItemType>::NumberOfNodes() const
{
  return (CountNodes(root));
}

template <class ItemType>
int CountNodes(TreeNode<ItemType> *tree)
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template <class ItemType>
void TreeType<ItemType>::InsertItem(ItemType newItem)
// Pre:  list is not full
// 		 item is not in tree
// Pre: newItem is not exist in the tree.
{
  insert(root, newItem);
}

template <class ItemType>
void insert(TreeNode<ItemType>* &tree, ItemType newItem)
// insert item to tree using recursion
{
  if (tree == NULL){ // base case
    tree = new TreeNode<ItemType>;
    tree->info = newItem;
    tree->left = NULL;
    tree->right = NULL;
  }
  else if (tree->info > newItem) // insert at left subtree.
    insert(tree->left, newItem);
  else
    insert(tree->right, newItem); // insert at right subtree.
}

template <class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Pre: tree is not empty
//      item's key has been initialized.
//      An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
  Delete(root, item);
}

template <class ItemType>
void Delete(TreeNode<ItemType>* &tree, ItemType item)
// function: determine the node of the node to be deleted and delete it using deleteNode function
{
  if (item < tree->info) // if the item less than node delete in left subtree.
    Delete(tree->left, item);
  else if (item > tree->info) // if the item greater than node delete in right subtree.
    Delete(tree->right, item);
  else // base case: node founded
    deleteNode(tree);
}

template <class ItemType>
void deleteNode(TreeNode<ItemType>* &tree)
{
  ItemType data;
  TreeNode<ItemType>* tempPtr = tree;
  
  // Case1: Deleting a node with only one child or Deleting leaf
  if(tree->left == NULL) { // 1.1. have right child or not
    tree = tree->right;
    delete tempPtr;
  }
  else if(tree->right == NULL) { // 1.2. have left child or not
    tree = tree->left;
    delete tempPtr;
  }
  // Case2: Deleting a node with two children
  else { // replace the greatest element in left subtree (Predecessor) with it and delete predecessor node
    // find the predecessor (it is the rightmost node in the left subtree) 
    GetPredecessor(tree->left, data);
    // Replace the data of the node to be deleted with predecessor's data
    tree->info = data;
    Delete(tree->left, data); // delete the node with the same way
  }
}

template<class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
{
  while(tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

template <class ItemType>
void TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
  retrieve(root, item, found);
}

template <class ItemType>
void retrieve(TreeNode<ItemType> *tree, ItemType& item, bool& found)
// Post: If found, item's key matches an element's key in the 
//       tree and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
  if (tree == NULL) // base case 1
    found = false;
  else if (tree->info > item) 
    retrieve(tree->left, item, found); // search in the left subtree
  else if (tree->info < item)
    retrieve(tree->right, item, found); // search in the right subtree
  else {  // base case 2
    found = true;
    item = tree->info;
  }
}

template <class ItemType>
void TreeType<ItemType>::PrintTree(OrderType order) const
{
  switch (order) {
    case IN_ORDER:
      PrintInOrder(root);
      break;
    case PRE_ORDER:
      PrintPreOrder(root);
      break;
    case POST_ORDER:
      PrintPostOrder(root);
      break;
    default:
      std::cout << "You Entered incorrect value.";
  }
}

template <class ItemType>
void PrintInOrder(TreeNode<ItemType> *tree)
{
  if (tree != NULL){
    PrintInOrder(tree->left);
    std::cout << tree->info << "\t";
    PrintInOrder(tree->right);
  }
}
template <class ItemType>
void PrintPostOrder(TreeNode<ItemType> *tree)
{
  if (tree != NULL){
    PrintPostOrder(tree->left);
    PrintPostOrder(tree->right);
    std::cout << tree->info << "\t";
  }

}

template <class ItemType>
void PrintPreOrder(TreeNode<ItemType> *tree)
{
  if (tree != NULL){
    std::cout << tree->info << "\t";
    PrintPreOrder(tree->left);
    PrintPreOrder(tree->right);
  }
}

template <class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order)
// For efficiency, ResetTree stores in a queue the results of the specified tree traversal
// Then, GetNextItem, dequeues the node values from the queue 
{
  switch(order) {
    case PRE_ORDER: PreOrder(root, preQue);
      break;
    case IN_ORDER:  InOrder(root, inQue);
      break;
    case POST_ORDER: PostOrder(root, postQue);
      break;
    default:
      std::cout << "You entered incorrect value!";
  }
}

template <class ItemType>
void InOrder(TreeNode<ItemType> *tree, QueueType<ItemType> &inQue)
{
  if(tree != NULL) {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}
template<class ItemType>
void PostOrder(TreeNode<ItemType> *tree, QueueType<ItemType> &postQue)
{
  if(tree != NULL) {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}
template<class ItemType>
void PreOrder(TreeNode<ItemType> *tree, QueueType<ItemType> &preQue)
{
  if (tree != NULL) {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}
template <class ItemType>
void TreeType<ItemType>::GetNextItem(ItemType &item, OrderType order, bool& finished)
// Pre:  ResetList was called with the same order. 
//       Queue has been initialized and not empty
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, finished be true.
{
  finished = false;
  switch (order) {
    case PRE_ORDER:
      preQue.Dequeue(item);
      if (preQue.IsEmpty())
        finished = true;
      break;
    case IN_ORDER:
      inQue.Dequeue(item);
      if (inQue.IsEmpty())
        finished = true;
      break;
    case POST_ORDER:
      postQue.Dequeue(item);
      if (postQue.IsEmpty())
        finished = true;
      break;
  }
}

#endif //TREETYPE_H
