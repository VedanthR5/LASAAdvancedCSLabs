/*
 * LaQueue
 *
 *
 * This is part of a series of labs for the Liberal Arts and Science Academy.
 * The series of labs provides a mockup of an POSIX Operating System
 * referred to as LA(SA)nix or LAnix.
 *
 * (c) copyright 2018, James Shockey - all rights reserved
 *
 * */
#include <climits>

using namespace std;
struct Node {
  int priority;
  void *data;
  struct Node *next;

  // Node Constructor?
  Node(void *data, int priority) {
    this->data = data;
    this->priority = priority;
    this->next = nullptr;
  }
};

class PQueue {

  

public:
Node *head;
  PQueue() {
    // front = nullptr;
    head = new Node(nullptr, INT_MIN);
  }

  void push(void *item, int priority);
  void *top();
  void pop();
  bool isEmpty();
  void display();
};