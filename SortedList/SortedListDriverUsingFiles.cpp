// Test driver with files
// TODO: reforme the code 
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "sorted.h"

using namespace std;
void PrintList(ofstream& outFile, SortedType list);

int main()
{

  ifstream inFile;       // file containing operations
  ofstream outFile;      // file containing output
  string inFileName;     // input file external name
  string outFileName;    // output file external name
  string outputLabel;     
  string command;        // operation to be executed
  
  int number;
  ItemType item;
  SortedType list;
  bool found;
  int numCommands;


  // Prompt for file names, read file names, and prepare files
  cout << "Enter name of input command file; press return." << endl;
  cin  >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return." << endl;
  cin  >> outFileName;
  outFile.open(outFileName.c_str());

  cout << "Enter name of test run; press return." << endl;
  cin  >> outputLabel;
  outFile << outputLabel << endl;

  inFile >> command;

  numCommands = 0;
  while (command != "Quit")
  { 
    outFile << command;
    if (command == "PutItem")
    {
      inFile >> number; 
      item.Initialize(number);
      list.PutItem(item);
      item.Print(outFile);
      outFile << " is inserted" << endl;
    }
    else if (command == "DeleteItem")
    {
      inFile >> number;
      item.Initialize(number);
      list.DeleteItem(item);
      item.Print(outFile);
      outFile << " is deleted" << endl;
    }
    else if (command == "GetItem")
    {
      inFile >> number;
      item.Initialize(number);
      list.GetItem(item, found);
      if (found)
        outFile << number << " found in list." << endl;
      else outFile << number  << " not in list."  << endl;  
    } 
    else if (command == "GetLength")  
      outFile << " Length is " << list.GetLength() << endl;
    else if (command == "IsFull")
      if (list.IsFull())
        outFile << "List is full." << endl;
      else outFile << "List is not full."  << endl;  
    else if (command == "MakeEmpty")
      list.MakeEmpty();
    else if (command == "PrintList")
      PrintList(outFile, list);
    else if (command == "Search") {
      inFile >> number;
      item.Initialize(number);
      bool found;
      list.Search(item, found);
      outFile << " Item " << number << " was found: " << found << endl;
    } 
    else cout << " Command not recognized." << endl;
    numCommands++;
    cout <<  " Command number " << numCommands << " completed." 
         << endl;
    inFile >> command;   
  };
 
  cout << "Quit"  << endl << "Testing completed."  << endl;
  inFile.close();
  outFile.close();
  return 0;
}


void PrintList(ofstream& dataFile, SortedType list)
// Pre:  list has been initialized.      
//       dataFile is open for writing.   
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.         
{
  int length;
  ItemType item;

  list.ResetList();
  length = list.GetLength();
  for (int counter = 1; counter <= length; counter++)
  {
    ItemType item;
    item = list.GetNextItem();
    item.Print(dataFile);
  }
  dataFile << endl;
}


