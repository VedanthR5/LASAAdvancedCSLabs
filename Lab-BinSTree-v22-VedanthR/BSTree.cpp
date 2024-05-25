/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it
 * tests
 */

#include "BSTree.h"
#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */

void BST::find(int item_key, node **prnt, node **loc) {
  node *ptr, *ptrsave;
  if (root == NULL) {
    *loc = NULL;
    *prnt = NULL;
    return;
  }
  if (item_key == root->key_value) {
    *loc = root;
    *prnt = NULL;
    return;
  }
  if (item_key < root->key_value)
    ptr = root->p_left;
  else
    ptr = root->p_right;
  ptrsave = root;
  while (ptr != NULL) {
    if (item_key == ptr->key_value) {
      *loc = ptr;
      *prnt = ptrsave;
      return;
    }
    ptrsave = ptr;
    if (item_key < ptr->key_value)
      ptr = ptr->p_left;
    else
      ptr = ptr->p_right;
  }
  *loc = NULL;
  *prnt = ptrsave;
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode) {
  // assume newnode has all assigned parameters
  //  if (we are at root)
  if (!tree) {
    // Just create a single node for root to point to,
    //    with all the data in it.
    root = newnode;
    return;
  }
  // if (there is already a node with our key value)
  if (newnode->key_value == tree->key_value) {
    // Just return
    return;
  }

  // if (the new node is less than the current node)
  if (newnode->key_value < tree->key_value) {

    // if (see if something is already a child on the left)
    if (tree->p_left) {
      // if so, the recurse insert at this subtree
      insert(tree->p_left, newnode);
    } else {
      // otherwise the new node goes here as a leaf (ie no children)
      tree->p_left = newnode;
      return;
    }
  } else // it must be to the right
  {
    // if (is there already a child on right?)
    if (tree->p_right) {
      // if so, the recurse insert at this subtree
      insert(tree->p_right, newnode);
    } else {
      tree->p_right = newnode;
      // otherwise the new node goes here as a leaf (ie no children)
      return;
    }
  }
}

/*
 * Delete Element from the tree
 */
void BST::remove(int item) {
  node *parent, *location;
  if (root == NULL) {
    cout << "Tree empty" << endl;
    return;
  }
  find(item, &parent, &location);
  if (location == NULL) {
    cout << "Item not present in tree" << endl;
    return;
  }
  if (location->p_left == nullptr && location->p_right == nullptr) {
    case_0(parent, location);
  } else if (location->p_left != nullptr && location->p_right == nullptr) {
    case_1(parent, location);
  } else if (location->p_right != nullptr && location->p_left == nullptr) {
    case_1(parent, location);
  } else{
    case_2(parent, location);
  }
  free(location);
}

/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(node *prnt, node *loc) {
  // if (we are at the root)
  if (prnt == NULL) {
    root = NULL;
    // update the root
  } else {
    if (prnt->p_left == loc) {
      prnt->p_left = NULL;
    } else {
      prnt->p_right = NULL;
    }
  }
}

/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(node *prnt, node *loc) {
  node *child;
  if (loc->p_left != NULL) {
    child = loc->p_left;
  } else {
    child = loc->p_right;
  }
  if (prnt == NULL) {
    root = child;
  } else {
    if (prnt->p_left == loc) {
      prnt->p_left = child;
    } else {
      prnt->p_right = child;
    }
  }
}

/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(node *prnt, node *loc) {
  node *ptr, *ptrsave, *suc, *parsuc;
  // Find in-order successor and its parent.
  ptrsave = loc;
  ptr = loc->p_right;
  while (ptr->p_left != 
    NULL) {
    ptrsave = ptr;
    ptr = ptr->p_left;
  }
  suc = ptr;
  parsuc = ptrsave;
  if (suc->p_left == NULL && suc->p_right == NULL)
    case_0(parsuc, suc);
  else
    case_1(parsuc, suc);
  if (prnt == NULL) {
    root = suc;
  } else {
    if (loc == prnt->p_left)
      prnt->p_left = suc;
    else
      prnt->p_right = suc;
  }
  suc->p_left = loc->p_left;
  suc->p_right = loc->p_right;
}


/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level) {
  int i;
  if (ptr != NULL) {
    display(ptr->p_right, level + 1);
    cout << endl;
    if (ptr == root)
      cout << "Root->:  ";
    else {
      for (i = 0; i < level; i++)
        cout << "       ";
    }
    cout << ptr->key_value;
    display(ptr->p_left, level + 1);
  }
}
