#include "PQueue.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <climits>

bool PQueue::isEmpty() {
  // 'head' is pointing to a NULL pointer.
  if (!head->next)
    return true;
  else
    return false;
}

void PQueue::push(void* tskNumber, int priority)
  {
      Node* newnode = new Node(tskNumber, priority);

      Node* temp = head;
      if(isEmpty())
      {
          head->next = newnode;
      }
      else
      {
          while(temp->next && temp->next->priority<=priority)
          {
              temp = temp->next;
          }
          newnode->next = temp->next;
          temp->next = newnode;
      }
}

//----------------------------top------------------------------//
void* PQueue::top() {
  // Priority Queue is empty.
  if (isEmpty()) {
    // std::cout << "Nothing left to peek!\n";
    return(nullptr);
  } else {
    return head->next->data;
  }
}
//------------------------------
  void PQueue::pop() {
    // List is empty.
    if (head->next == NULL)
      return;

    // Storing the first node in a temporary variable.
    Node *temp = head->next;

    // Shifting Next pointer of head node.
    head->next = head->next->next;

    // Free the first node.
    free(temp);
  }
//-----------------------------------
  void PQueue::display() {
    Node *ptr;
    ptr = head;
    if (head == nullptr)
      std::cout << "Queue is empty\n";
    else {
      std::cout << "Queue is :\n";
      std::cout << "Priority       Item\n";
      while (ptr != nullptr) {
        std::cout << ptr->priority << "            " << (char *)ptr->data
                  << std::endl;
        ptr = ptr->next;
      }
    }
  }
