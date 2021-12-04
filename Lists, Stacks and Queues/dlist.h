#ifndef __DLIST_H__
#define __DLIST_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>


/**********************************************************
 * INSTRUCTOR NOTE: Do not modify the class declarations! *
 * The class Dlist is a class template.                   *
 *********************************************************/
class emptyList {
  // OVERVIEW: an exception class
};

template <typename T>
class Dlist {
  // OVERVIEW: contains a double-ended list of Objects

 public:
  // Maintenance methods

  
  Dlist();                                // constructor
  Dlist(const Dlist &l);                  // copy constructor
  Dlist &operator=(const Dlist &l);       // assignment
  ~Dlist();                               // destructor

  // Operational methods

  

  // EFFECTS: returns true if list is empty, false otherwise
  bool IsEmpty() const;

  // MODIFIES: this
  // EFFECTS: inserts o at the front of the list

  void InsertFront(const T &o);
  // MODIFIES: this
  // EFFECTS: inserts o at the back of the list
  void InsertBack(const T &o);

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveFront();

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveBack();

 private:
  // A private type

  struct node {
    node   *next;
    node   *prev;
    T      o;
  };

  // Private member variables

  node   *first; // The pointer to the first node (nullptr if none)
  node   *last;  // The pointer to the last node (nullptr if none)

  // Private utility methods

  // EFFECTS: called by constructors to establish empty list invariant
  void MakeEmpty();

  // EFFECTS: called by copy constructor/operator= to copy nodes
  //          from a source instance l to this instance
  void CopyAll(const Dlist &l);
    
  // EFFECTS: called by destructor and operator= to remove and destroy
  //          all list nodes
  void RemoveAll();
  
  void printAll();
};

// Constructor
template <typename T>
Dlist<T>::Dlist() {
  MakeEmpty();
}

// Copy constructor
template <typename T>
Dlist<T>::Dlist(const Dlist &l) {
  MakeEmpty();
  CopyAll(l);
}

// Assignment operator
template <typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l) {
  if (this != &l) {
    RemoveAll();
    CopyAll(l);
  }
  return *this;
}

// Destructor
template <typename T>
Dlist<T>::~Dlist() {
  RemoveAll();
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/**********************************************************
 * INSTRUCTOR NOTE: Implement the member functions below. *
 * These member functions are all function templates.     *
 *********************************************************/

// EFFECTS: returns true if list is empty, false otherwise
/**********************************************************
 if first and Last = NULL
 return true
 else
 return false

 Logic: if first and last pointers are NULL, there is
 nothing in the list
 *********************************************************/
template <typename T>
bool Dlist<T>::IsEmpty() const {
  if (first == NULL && last == NULL)
  return true;
  else
  return false;
}

// MODIFIES: this //PSEUDOCODE
// EFFECTS: inserts o at the front of the list
/**********************************************************
temp = new node
 if list = empty
 last = temp
 else
 first prev = temp

 temp prev = NULL
 temp o = o
 temp next = first
 first = temp

 Logic: if list is empty, new node is now last.
 else first node prev is now temp. temp prev is null, temp
 next is first. Assign data to temp and now point first to
 new node.
 *********************************************************/
template <typename T>
void Dlist<T>::InsertFront(const T& o) {
node* temp=(node*)malloc(sizeof(struct node));

if (IsEmpty())
  last = temp;
else
first->prev=temp;

 temp->prev=NULL;
 temp->o=o;
 temp->next=first;
first=temp;
}

// MODIFIES: this
// EFFECTS: inserts o at the back of the list
/**********************************************************
temp = new node
 if list = empty
 first = temp
 else
 last next = temp

 temp next = NULL
 temp o = o
 temp prev = last
 last = temp

 Logic: if list is empty, new node is now first.
 else last node next is now temp. temp next is null, temp
 prev is first. Assign data to temp and now point last to
 new node.
 *********************************************************/
template <typename T>
void Dlist<T>::InsertBack(const T& o) {
node* temp=(node*)malloc(sizeof(struct node));

if (IsEmpty())
  first = temp;
else
last->next=temp;

 temp->next=NULL;
 temp->o=o;
 temp->prev=last;
last=temp;
}

// MODIFIES: this
// EFFECTS: removes and returns first object from non-empty list
//          throws an instance of emptyList if empty
/**********************************************************
if list is empty
throw list

temp = first next
if temp is null
last = null
else
temp prev = null
o = first o
delete first
first = temp

 Logic: if list is empty, throw list.
 temp is equal to 2nd node.
 if temp is null, list has 1 node. set last to null
 else
 second node prev = null
 data = first data
 delete first
 first = second node
 *********************************************************/
template <typename T>
T Dlist<T>::RemoveFront() {
  if (IsEmpty())
  throw emptyList();
  
node* temp=first->next;
if (temp == NULL)
last = NULL;
else
temp->prev = NULL;
T o = first->o;
delete first;
first = temp;

return o;
}


// MODIFIES: this
// EFFECTS: removes and returns last object from non-empty list
//          throws an instance of emptyList if empty
/**********************************************************
if list is empty
throw list

temp = last prev
if temp is null
first = null
else
temp next = null
o = lst o
delete last
last = temp

 Logic: if list is empty, throw list.
 temp is equal to last prev.
 if temp is null, list has 1 node. set first to null
 else
 temp = null
 data = last data
 delete last
 last = temp
 *********************************************************/
template <typename T>
T Dlist<T>::RemoveBack()
{
 if (IsEmpty())
  throw emptyList();
  
node* temp=last->prev;
if (temp == NULL)
first = NULL;
else
temp->next = NULL;
T o = last->o;
delete last;
last = temp;

return o;
}

// EFFECTS: called by constructors to establish empty list invariant
/**********************************************************
first = null
last = null

 Logic: set pointers to null
 *********************************************************/
template <typename T>
void Dlist<T>::MakeEmpty() {
  first = NULL;
  last = NULL;
}

// EFFECTS: called by copy constructor/operator= to copy nodes
//          from a source instance l to this instance
/**********************************************************
for all node in l
o = node->o
insertback(o);

 Logic: for all nodes in list l, copy data into variable and
 insert in list using insertback function
 *********************************************************/
template <typename T>
void Dlist<T>::CopyAll(const Dlist &l) {

for (node* np = l.first; np != NULL; np = np->next){
T o = np->o;
InsertBack(o);
}

}

// EFFECTS: called by destructor and operator= to remove and destroy
//          all list nodes
/**********************************************************
while list !empty
RemoveFront()

 Logic: while list is not empty, use removefront function
 *********************************************************/
template <typename T>
void Dlist<T>::RemoveAll() {
  while (!IsEmpty())
  {
    RemoveFront();
  }
}

template <typename T>
void Dlist<T>:: printAll()
{
  node *traversal_node = first;
  while (traversal_node) {
    std::cout << "from print: " << traversal_node -> o << std::endl;
    traversal_node = traversal_node -> next;
  }
  traversal_node=nullptr;
  delete traversal_node;
}
/**** INSTRUCTOR NOTE: DO NOT DELETE #endif FROM END OF FILE. ****/
#endif /* __DLIST_H__ */
