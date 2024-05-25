//*****************************************************************
//  LinkedList.cpp
//  HashTable

//
//  This header file contains the Linked List class declaration.
//  Hash Table array elements consist of Linked List objects.
//*****************************************************************

#include "LinkedList.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList() {
  head = NULL;
  length = 0;
}

// Inserts an item at the end of the list.
void LinkedList::insert(Element *newElement) {
  if (head == nullptr) {
    // If the list is empty, set the new element as the head
    head = newElement;
  } else {
    // Traverse the list to find the last node
    Element *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    // Insert the new element after the last node
    temp->next = newElement;
  }
  length++; // Increase the length of the list
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::remove(string Key) {
  if (head == nullptr) // If list is empty
    return false;

  Element *temp = head;
  Element *prev = nullptr;

  // Traverse the list
  while (temp != nullptr) {
    // If the key is found
    if (temp->key == Key) {
      // If the node to remove is the head
      if (temp == head) {
        head = temp->next;
        delete temp;
      } else {
        prev->next = temp->next;
        delete temp;
      }
      length--; // Decrease the length of the list
      return true;
    }
    // Move to the next node
    prev = temp;
    temp = temp->next;
  }

  return false; // Key not found
}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Element *LinkedList::get(string Key) {

  Element *temp = head;
  while (temp != nullptr) {
    if (temp->key == Key) {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

// Displays list contents to the console window.
void LinkedList::printList() {
  if (length == 0) {
    cout << "\n{ }\n";
    return;
  }
  Element *p = head;
  Element *q = head;
  cout << "\n{ ";
  while (q) {
    p = q;
    // if (p != head)
    if (p != nullptr) {
      cout << p->key;
      if (p->next)
        cout << ", ";
      else
        cout << " ";
    }
    q = p->next;
  }
  cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength() { return length; }

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList() {
  Element *current = head;
  while (current != nullptr) {
    Element *next = current->next;
    delete current;
    current = next;
  }
  head = nullptr; // Set head to nullptr to indicate the list is empty
}

//*****************************************************************
// End of File
//*****************************************************************