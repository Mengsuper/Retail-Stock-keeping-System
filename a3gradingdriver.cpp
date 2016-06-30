// File:        a3gradingdriver.cpp
// Author:      Geoffrey Tien
// Date:        2016-06-18
// Description: Grading driver for CPSC 221 assignment #3
//              Calls to test functions are on lines 54 to 79.
//              If any function causes a runtime crash, comment out the
//              call to the offending test function and recompile.
//              Repeat as necessary until a final score can be returned.

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

#include "rbtree.h"
#include "stocksystem.h"

using namespace std;

// maximum test score definitions
const static double treetest1max = 7;
const static double treetest2max = 4;
const static double treetest3max = 7;
const static double treetest4max = 4;
const static double stocktest1max = 3;
const static double stocktest2max = 2;

// forward declarations
string PrintRBTreeInt(Node<int>* n);
string PrintRBTreeStockItem(Node<StockItem>* n);
string TreeIntArrToString(int* arr, int size);

double TreeTest1();
double TreeTest2();
double TreeTest3();
double TreeTest4();
double StockTest1();
double StockTest2();

int main()
{
  double treetest1score = 0;
  double treetest2score = 0;
  double treetest3score = 0;
  double treetest4score = 0;
  double stocktest1score = 0;
  double stocktest2score = 0;

  cout << "**************************************************************************\n"
       << "* Grading test driver for CMPT 225 A4  - RedBlackTree, StockSystem class *\n"
       << "**************************************************************************\n" << endl;

  cout << "Running red-black tree test #1..." << endl;
  treetest1score = TreeTest1();
  cout << "Red-black tree part 1 - Insert, DumpInOrder\n"
       << "Score: " << treetest1score << " / " << treetest1max << "\n" << endl;

  cout << "Running red-black tree test #2..." << endl;
  treetest2score = TreeTest2();
  cout << "Red-black tree part 2 - Size, Height, RemoveAll\n"
       << "Score: " << treetest2score << " / " << treetest2max << "\n" << endl;

  cout << "Running red-black tree test #3..." << endl;
  treetest3score = TreeTest3();
  cout << "Red-black tree part 3 - Remove, Height\n"
       << "Score: " << treetest3score << " / " << treetest3max << "\n" << endl;

  cout << "Running red-black tree test #4..." << endl;
  treetest4score = TreeTest4();
  cout << "Red-black tree part 4 - copy constructor, operator=\n"
       << "Score: " << treetest4score << " / " << treetest4max << "\n" << endl;

  cout << "Running stock system test #1..." << endl;
  stocktest1score = StockTest1();
  cout << "Stock system part 1 - StockNewItem, EditStockItemDescription, EditStockItemPrice\n"
       << "Score: " << stocktest1score << " / " << stocktest1max << "\n" << endl;

  cout << "Running stock system test #2..." << endl;
  stocktest2score = StockTest2();
  cout << "Stock system part 2 - Restock, Sell\n"
       << "Score: " << stocktest2score << " / " << stocktest2max << "\n" << endl;

  double testscore = treetest1score + treetest2score + treetest3score + treetest4score +
                  stocktest1score + stocktest2score;
  double maxscore = treetest1max + treetest2max + treetest3max + treetest4max +
                 stocktest1max + stocktest2max;

  cout << "Overall score: " << testscore << " / " << maxscore << "\n" << endl;

#ifdef _WIN32
  system("pause");
#endif
  return 0;
}

string PrintRBTreeInt(Node<int>* n)
{
  string result = "";
  ostringstream oss;
  if (n != NULL)
  {
    oss << n->data;
    result += oss.str();
    if (n->is_black)
      result += "* ";
    else
      result += "  ";
    result += PrintRBTreeInt(n->left);
    result += PrintRBTreeInt(n->right);
  }

  return result;
}

string PrintRBTreeStockItem(Node<StockItem>* n)
{
  string result = "";
  ostringstream oss;
  if (n != NULL)
  {
    result += "(";
    oss << n->data.GetSKU();
    result += oss.str();
    oss.str(""); // clear the stream for re-use
    if (n->is_black)
      result += "*,";
    else
      result += " ,";
    result += n->data.GetDescription() + ", ";
    oss << n->data.GetStock();
    result += (oss.str() + ", ");
    oss.str("");
    oss << n->data.GetPrice();
    result += (oss.str() + ")\n");
    oss.str("");
    result += PrintRBTreeStockItem(n->left);
    result += PrintRBTreeStockItem(n->right);
  }
  return result;
}

string TreeIntArrToString(int* arr, int size)
{
  string result = "";
  ostringstream oss;
  if (arr != NULL)
  {
    for (int i = 0; i < size; i++)
    {
      oss << arr[i];
      if (i < size-1)
        oss << " ";
    }
    result = oss.str();
  }
  return result;
}

// Tree - Insert
double TreeTest1()
{
  double score = 0;
  string preorderdump;
  string inorderstring;

  int* treecontentsinorder = NULL;
  int treecontentsize = 0;

  RBTree<int> tree;
  tree.Insert(22);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(22))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "22")
      score += 0.25;
    if (preorderdump == "22* ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  tree.Insert(11);
  tree.Insert(33);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(11) && tree.Contains(33))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "11 22 33")
      score += 0.25;
    if (preorderdump == "22* 11  33  ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  tree.Insert(77);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(77))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "11 22 33 77")
      score += 0.25;
    if (preorderdump == "22* 11* 33* 77  ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  tree.Insert(88);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(88))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "11 22 33 77 88")
      score += 0.25;
    if (preorderdump == "22* 11* 77* 33  88  ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  tree.Insert(99);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(99))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "11 22 33 77 88 99")
      score += 0.25;
    if (preorderdump == "22* 11* 77  33* 88* 99  ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  tree.Insert(101);
  tree.Insert(112);
  preorderdump = PrintRBTreeInt(tree.GetRoot());
  if (tree.Contains(101) && tree.Contains(112))
  {
    score += 0.5;
    treecontentsinorder = tree.DumpInOrder(treecontentsize);
    inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
    if (inorderstring == "11 22 33 77 88 99 101 112")
      score += 0.25;
    if (preorderdump == "77* 22  11* 33* 99  88* 101* 112  ") score += 0.25;

    delete[] treecontentsinorder;
    treecontentsize = 0;
  }
  if (!tree.Insert(112)) // duplicate item
  {
    score += 1;
  }

  return score;
}

// Tree - Size, Height
double TreeTest2()
{
  double score = 0;

  RBTree<int> tree;
  if (tree.Size() == 0)
  {
    score += 0.5;
    if (tree.Height() == 0) score += 0.5;
  }
  tree.Insert(22);
  if (tree.Size() == 1)
  {
    score += 0.5;
    if (tree.Height() == 1) score += 0.5;
  }
  tree.Insert(11);
  tree.Insert(33);
  if (tree.Size() == 3)
  {
    score += 0.5;
    if (tree.Height() == 2) score += 0.5;
  }
  tree.Insert(77);
  tree.Insert(88);
  tree.Insert(99);
  tree.Insert(101);
  tree.Insert(112);
  if (tree.Size() == 8)
  {
    score += 0.5;
    if (tree.Height() == 4) score += 0.5;
  }

  return score;
}

// Tree - Remove, Height, RemoveAll
double TreeTest3()
{
  double score = 0;
  string preorderdump;
  string inorderstring;

  int* treecontentsinorder = NULL;
  int treecontentsize = 0;

  RBTree<int> treeA;
  treeA.Insert(22);
  treeA.Insert(11);
  treeA.Insert(33);
  treeA.Insert(77);
  treeA.Insert(88);
  treeA.Insert(99);
  treeA.Insert(101);
  treeA.Insert(112);
  bool postringmatch = false;
  bool removeresult = false;
  bool iostringmatch = false;
  removeresult = treeA.Remove(112);
  preorderdump = PrintRBTreeInt(treeA.GetRoot());
  postringmatch = preorderdump == "77* 22  11* 33* 99  88* 101* ";
  treecontentsinorder = treeA.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 33 77 88 99 101";
  if (removeresult && treeA.Size() == 7 && iostringmatch)
  {
    score += 0.5;
    if (treeA.Height() == 3) score += 0.25;
    if (postringmatch) score += 0.25;
  }
  postringmatch = false;
  removeresult = false;
  iostringmatch = false;
  delete[] treecontentsinorder;
  treecontentsize = 0;

  removeresult = treeA.Remove(99);
  preorderdump = PrintRBTreeInt(treeA.GetRoot());
  postringmatch = preorderdump == "77* 22  11* 33* 88* 101  ";
  treecontentsinorder = treeA.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 33 77 88 101";
  if (removeresult && treeA.Size() == 6 && iostringmatch)
  {
    score += 0.5;
    if (treeA.Height() == 3) score += 0.25;
    if (postringmatch) score += 0.25;
  }
  postringmatch = false;
  removeresult = false;
  iostringmatch = false;
  delete[] treecontentsinorder;
  treecontentsize = 0;

  removeresult = treeA.Remove(88);
  preorderdump = PrintRBTreeInt(treeA.GetRoot());
  postringmatch = preorderdump == "77* 22  11* 33* 101* ";
  treecontentsinorder = treeA.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 33 77 101";
  if (removeresult && treeA.Size() == 5 && iostringmatch)
  {
    score += 0.5;
    if (treeA.Height() == 3) score += 0.25;
    if (postringmatch) score += 0.25;
  }
  postringmatch = false;
  removeresult = false;
  iostringmatch = false;
  delete[] treecontentsinorder;
  treecontentsize = 0;

  removeresult = treeA.Remove(77);
  preorderdump = PrintRBTreeInt(treeA.GetRoot());
  postringmatch = preorderdump == "33* 22* 11  101* ";
  treecontentsinorder = treeA.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 33 101";
  if (removeresult && treeA.Size() == 4 && iostringmatch)
  {
    score += 0.5;
    if (treeA.Height() == 3) score += 0.25;
    if (postringmatch) score += 0.25;
  }
  postringmatch = false;
  removeresult = false;
  iostringmatch = false;
  delete[] treecontentsinorder;
  treecontentsize = 0;

  treeA.RemoveAll();
  preorderdump = PrintRBTreeInt(treeA.GetRoot());
  postringmatch = preorderdump == "";
  if (treeA.Size() == 0 && postringmatch)
  {
    score += 0.5;
    if (treeA.Height() == 0) score += 0.5;
  }

  RBTree<int> treeB; // remove from empty tree
  if (!treeB.Remove(321) && treeB.Size() == 0)
  {
    score += 0.5;
    if (treeB.Height() == 0) score += 0.5;
  }
  bool insertresult = treeB.Insert(22);
  bool removenonexist = treeB.Remove(321);
  bool removeonly = treeB.Remove(22); // remove the only item
  preorderdump = PrintRBTreeInt(treeB.GetRoot());
  postringmatch = preorderdump == "";
  if (insertresult && treeB.Size() == 0 && postringmatch && !removenonexist)
  {
    score += 0.5;
    if (treeB.Height() == 0) score += 0.5;
  }

  return score;
}

// Tree - Copy constructor, operator=
double TreeTest4()
{
  double score = 0;

  RBTree<int> treeA;
  treeA.Insert(22);
  treeA.Insert(88);
  treeA.Insert(77);
  treeA.Insert(99);
  treeA.Insert(11);

  string preorderdump = "";
  string inorderstring = "";
  bool postringmatch = false;
  bool iostringmatch = false;
  int* treecontentsinorder = NULL;
  int treecontentsize = 0;

  RBTree<int> treeB(treeA);
  preorderdump = PrintRBTreeInt(treeB.GetRoot());
  postringmatch = preorderdump == "77* 22* 11  88* 99  ";
  treecontentsinorder = treeB.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 77 88 99";
  if (iostringmatch && treeB.Size() == 5 && treeB.Height() == 3)
  {
    score += 0.5;
    if (postringmatch) score += 0.5;
  }
  delete[] treecontentsinorder;
  treecontentsize = 0;

  RBTree<int> treeC;
  bool insertresult = treeC.Insert(123);
  treeC = treeA;
  preorderdump = PrintRBTreeInt(treeC.GetRoot());
  postringmatch = preorderdump == "77* 22* 11  88* 99  ";
  treecontentsinorder = treeC.DumpInOrder(treecontentsize);
  inorderstring = TreeIntArrToString(treecontentsinorder, treecontentsize);
  iostringmatch = inorderstring == "11 22 77 88 99";
  if (insertresult && iostringmatch && treeC.Size() == 5 && treeC.Height() == 3)
  {
    score += 0.5;
    if (postringmatch) score += 0.5;
  }

  // write an empty tree into a non-empty tree
  RBTree<int> treeD;
  RBTree<int> treeE; // leave this empty
  insertresult = treeD.Insert(22);
  treeD = treeE;
  preorderdump = PrintRBTreeInt(treeD.GetRoot());
  postringmatch = preorderdump == "";
  if (insertresult && postringmatch)
  {
    score += 0.5;
    if (treeD.Size() == 0 && treeD.Height() == 0)
      score += 0.5;
  }

  // assign a tree to itself
  RBTree<int> treeF;
  treeF.Insert(22);
  treeF = treeF;
  preorderdump = PrintRBTreeInt(treeF.GetRoot());
  postringmatch = preorderdump == "22* ";
  if (insertresult && postringmatch)
  {
    score += 0.5;
    if (treeF.Size() == 1 && treeF.Height() == 1)
      score += 0.5;
  }

  return score;
}

// Stock System will not be thoroughly tested.

// Stock system - StockNewItem, EditStockItemDescription, EditStockItemPrice
double StockTest1()
{
  int score = 0;

  StockSystem ss;
  ss.StockNewItem(StockItem(10001, "orange", 1));
  string preorderdump = PrintRBTreeStockItem(ss.GetRecords().GetRoot());
  bool stringmatch = preorderdump == "(10001*,orange, 0, 1)\n";
  if (stringmatch) score += 1;

  ss.EditStockItemDescription(10001, "apple");
  preorderdump = PrintRBTreeStockItem(ss.GetRecords().GetRoot());
  stringmatch = preorderdump == "(10001*,apple, 0, 1)\n";
  if (stringmatch) score += 1;

  ss.EditStockItemPrice(10001, 2);
  preorderdump = PrintRBTreeStockItem(ss.GetRecords().GetRoot());
  stringmatch = preorderdump == "(10001*,apple, 0, 2)\n";
  if (stringmatch) score += 1;

  return score;
}

// Stock system - Restock, Sell, GetBalance
double StockTest2()
{
  int score = 0;

  StockSystem ss;
  ss.StockNewItem(StockItem(10001, "orange", 1));
  bool cannotafford = ss.Restock(10001, 100, 100000);
  bool canafford = ss.Restock(10001, 200, 0.5);
  string preorderdump = PrintRBTreeStockItem(ss.GetRecords().GetRoot());
  bool stringmatch = preorderdump == "(10001*,orange, 200, 1)\n";
  if (!cannotafford && canafford && ss.GetBalance() == 99900 && stringmatch) score += 1;

  ss.StockNewItem(StockItem(10002, "apple", 1));
  bool nostock = ss.Sell(10002, 100);
  bool cansell = ss.Sell(10001, 100);
  preorderdump = PrintRBTreeStockItem(ss.GetRecords().GetRoot());
  stringmatch = preorderdump == "(10001*,orange, 100, 1)\n(10002 ,apple, 0, 1)\n";
  if (!nostock && cansell && ss.GetBalance() == 100000 && stringmatch) score += 1;

  return score;
}