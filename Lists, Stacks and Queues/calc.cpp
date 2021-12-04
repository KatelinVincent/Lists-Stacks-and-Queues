// Run in repl.it:
// clang++-7 -pthread -std=c++17 -o calc calc.cpp; ./calc < calc_test1.in

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include "dlist.h"
#include <stack>

/*
  operations: + add
              - subtract
              * multiply
              / divide
              n negate top item
              d duplicate top item
              r reverse top two items
              p print top item
              c clear entire stack
              a print all items
              q quit
*/

class divZero {};
class badInput {};

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/*******************************************************
 * INSTRUCTOR NOTE: Implement the functions below.     *
 * You may throw exception classes emptyList, divZero, *
 * or badInput from these functions as needed.         *
 ******************************************************/

// EFFECTS: performs + operation
/**********************************************************
if stack = empty
thhrow list

pop first node
if list = empty{
push node back on stack
throw list}

pop second node
push first+second

 *********************************************************/
void DoAdd(Dlist<double> &stack) {
 double temp1 = stack.RemoveFront();
 
 if (stack.IsEmpty()){
  stack.InsertFront(temp1);
  throw emptyList();
 }
 double temp2 = stack.RemoveFront();
  stack.InsertFront(temp1 + temp2);
}


// EFFECTS: performs - operation
/**********************************************************
if stack = empty
thhrow list

pop first node
if list = empty{
push node back on stack
throw list}

pop second node
push second-first

 *********************************************************/
void DoSub(Dlist<double> &stack) {
  double temp2 = stack.RemoveFront();
 
  if (stack.IsEmpty()){
    stack.InsertFront(temp2);
    throw emptyList();
  }
  double temp1 = stack.RemoveFront();

  stack.InsertFront(temp1 - temp2);
}

// EFFECTS: performs * operation
/**********************************************************
if stack = empty
thhrow list

pop first node
if list = empty{
push node back on stack
throw list}

pop second node
push first*second
 *********************************************************/
void DoMult(Dlist<double> &stack) {
  double temp2 = stack.RemoveFront();
 
  if (stack.IsEmpty()){
    stack.InsertFront(temp2);
    throw emptyList();
  }
  double temp1 = stack.RemoveFront();

  stack.InsertFront(temp1 * temp2);
  
}

// EFFECTS: performs / operation
/**********************************************************
if stack = empty
thhrow list

pop first node
if list = empty{
push node back on stack
throw list}

pop second node

if first node = 0{
push second node
push first node}

push second/first

 *********************************************************/
void DoDiv(Dlist<double> &stack) {
  double temp2 = stack.RemoveFront();
 
  if (stack.IsEmpty()){
    stack.InsertFront(temp2);
    throw emptyList();
  }
  double temp1 = stack.RemoveFront();

  if (temp2 == 0)
  {
    stack.InsertFront(temp1);
    stack.InsertFront(temp2);
    throw divZero();
  }
  stack.InsertFront(temp1/temp2);
}

/**********************************************************
if stack = empty
throw list

pop first node

push first*-1

 *********************************************************/
void DoNeg(Dlist<double> &stack) {
  double temp1 = stack.RemoveFront();
  temp1 = temp1 * -1;
  stack.InsertFront(temp1);
}

// EFFECTS: performs d operation
/**********************************************************
if stack = empty
throw list

pop first node
push first node
push first node
 *********************************************************/
void DoDup(Dlist<double> &stack) {
  double temp1 = stack.RemoveFront();
  stack.InsertFront(temp1);
  stack.InsertFront(temp1);
}

// EFFECTS: performs r operation
/**********************************************************
if stack = empty
throw list

pop first node
if list = empty{
push node back on stack
throw list}

pop second node

push first
push second
 *********************************************************/
void DoRev(Dlist<double> &stack) {
  double temp2 = stack.RemoveFront();
 
  if (stack.IsEmpty()){
    stack.InsertFront(temp2);
    throw emptyList();
  }
  double temp1 = stack.RemoveFront();
  stack.InsertFront(temp2);
  stack.InsertFront(temp1);
}

// EFFECTS: performs p operation
/**********************************************************
temp = pop first node
print first node
 *********************************************************/
void DoPrint(Dlist<double> &stack) {
  double temp1 = stack.RemoveFront();
  std::cout << temp1 << std::endl;
  stack.InsertFront(temp1);
}

// EFFECTS: performs c operation
/**********************************************************
while stack !empty
remove first
 *********************************************************/
void DoClear(Dlist<double> &stack) {
  while (!stack.IsEmpty())
  {
    stack.RemoveFront();
  }
}

// EFFECTS: performs a operation
/**********************************************************
while stack !empty{
print first
remove first}
 *********************************************************/
void DoPrintAll(Dlist<double> &stack) {
  Dlist<double> temp_s = stack;
  while (!temp_s.IsEmpty())
  {
    double temp1 = temp_s.RemoveFront();
    std::cout << temp1;
    if (!temp_s.IsEmpty()) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY BELOW THIS LINE ****/

bool DoOne(Dlist<double> &stack) {
  std::string s;
  double d;

  std::cin >> s;
  switch (s[0]) {
  case '+':
    DoAdd(stack);
    break;
  case '-':
    DoSub(stack);
    break;
  case '*':
    DoMult(stack);
    break;
  case '/':
    DoDiv(stack);
    break;
  case 'n':
    DoNeg(stack);
    break;
  case 'd':
      DoDup(stack);
      break;
  case 'r':
      DoRev(stack);
      break;
  case 'p':
      DoPrint(stack);
      break;
  case 'c':
      DoClear(stack);
      break;
  case 'a':
      DoPrintAll(stack);
      break;
  case 'q':
      return true;
      break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
      d = std::atof(s.c_str());
    stack.InsertFront(d);
      break;
  default:
      badInput e;
      throw e;
      break;
  }
  return false;
}

int main() {
  Dlist<double> stack;

  bool done = false;
  while (!done) {
    try {
      done = DoOne(stack);
    } catch (emptyList e) {
      std::cout << "Not enough operands\n";
    } catch (divZero e) {
      std::cout << "Divide by zero\n";
    } catch (badInput e) {
      std::cout << "Bad input\n";
    }
  }
}
