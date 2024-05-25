/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 		LASAalloc.h
 * 		LASAalloc class declaration.
 *
 * 		Do not change this file other than to add local varaibles and
 * Functions. Make any changes only in the provided block.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "LASAalloc.h"
#include <iostream>
#include <stdlib.h>

// Defines for LASAalloc buffer simulation.
// Keep it simple, no changes to program break
#define INITIAL_MALLOC_SIZE 100000
#define MAX_MALLOC_SIZE 100000

using namespace std;

typedef unsigned char BYTE_t;

LASAalloc::LASAalloc() {
  brk(INITIAL_MALLOC_SIZE);

  // Point to where first node will be located.
  block *firstBlock = (block *)bufferBase;
  freeList = firstBlock;

  // Configure first node on freeList
  firstBlock->size = (int)(bufferSize);
  firstBlock->prev_block = nullptr;
  firstBlock->next_block = nullptr;
  firstBlock->this_block_data =
      (void *)((long long int)bufferBase + (long long int)sizeof(block));
  firstBlock->freeFlag = true;

  // Show initial statistics
  cout << "buffer Allocation: " << bufferBase << " - " << brk(0) << endl;
  cout << "freeList: " << freeList << " - " << brk(0) << endl;
  cout << "Block header size " << sizeof(block) << endl;
  cout << "integer size " << sizeof(int) << endl;

  display_node(freeList);
}

// todo: destructor
LASAalloc::~LASAalloc() { free(bufferBase); }

void LASAalloc::display_node(struct block *p) {
  cout << "block: " << p << endl;
  cout << "\t\tsize: " << p->size << endl;
  cout << "\t\tnext: " << p->next_block << endl;
  cout << "\t\tprev: " << p->prev_block << endl;
  cout << "\t\tbuffer: " << p->this_block_data << endl;
}

void LASAalloc::display() {
    struct block *p;
    if (freeList == nullptr) {
        cout<<"List is empty\n\n\n";
        return;
    }
    p = freeList;

    cout<<"List is:\n";
    while(p != nullptr) {
        display_node(p);
        p=p->next_block;
    }
    cout << endl;
}


void *LASAalloc::lalloc(int size) {

  // if block can fit...
  // change the size of the freelist to the size
  block *header = freeList;
  size = ((size + 7) & (-8)); // round

  while (header != nullptr) {
    if (size > header->size) {
      header = header->next_block;
      if (header == nullptr) {
        cout << "Out of memory" << endl;
        return nullptr;
      }
      continue;
    }
    if (size + 32 >= header->size) {
      if (header->next_block == nullptr && header->prev_block == nullptr) {
        freeList = nullptr;
      } else if (header->next_block == nullptr &&
                 header->prev_block != nullptr) {
        header->prev_block->next_block = nullptr;
      } else if (header->next_block != nullptr &&
                 header->prev_block == nullptr) {
        header->next_block->prev_block = nullptr;
        freeList = header->next_block;
      } else {
        header->next_block->prev_block = header->prev_block;
        header->prev_block->next_block = header->next_block;
      }
    } else {
      auto *new_header = (struct block *)((BYTE_t *)header + 32 + size);
      new_header->size = header->size - 32 - size;
      new_header->this_block_data = (BYTE_t *)new_header + 32;

      if (header->next_block == nullptr && header->prev_block == nullptr) {
        new_header->next_block = nullptr;
        new_header->prev_block = nullptr;
        freeList = new_header;
      } else if (header->next_block == nullptr &&
                 header->prev_block != nullptr) {
        new_header->next_block = nullptr;
        new_header->prev_block = header->prev_block;
      } else if (header->next_block != nullptr &&
                 header->prev_block == nullptr) {
        new_header->next_block = header->next_block;
        new_header->prev_block = nullptr;
        freeList = new_header;
      } else {
        new_header->next_block = header->next_block;
        new_header->prev_block = header->prev_block;
      }

      header->size = size;
    }

    return header->this_block_data;
  }

  cout << "Memory not allocated" << endl;
  return nullptr; // no suitable memory block found
}

void* LASAalloc::lfree(void *userBlock) {
  block *header = freeList;
  auto *alloc = (struct block *)((BYTE_t *)userBlock - 32);

  if (header == nullptr) {
    freeList = alloc;
    return nullptr;
  }

  while (true) {
    if (header->prev_block == nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        header->prev_block = alloc;
        freeList = alloc;
        break;
      }
    } else if (header->next_block == nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        alloc->prev_block = header->prev_block;
        header->prev_block->next_block = alloc;
        header->prev_block = alloc;
      } else {
        alloc->prev_block = header;
        header->next_block = alloc;
      }
      break;
    } else if (header->prev_block != nullptr && header->next_block != nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        alloc->prev_block = header->prev_block;
        header->prev_block->next_block = alloc;
        header->prev_block = alloc;
        break;
      }
    }

    header = header->next_block;
  }

  if (alloc->next_block != nullptr &&
      (struct block *)((BYTE_t *)alloc->this_block_data + alloc->size) ==
          alloc->next_block) {
    // Merge right
    alloc->next_block = alloc->next_block->next_block;
    if (alloc->next_block != nullptr)
      alloc->next_block->prev_block = alloc;
    alloc->size = alloc->size + alloc->next_block->size + 32;
  }
  if (alloc->prev_block != nullptr &&
      (struct block *)((BYTE_t *)alloc->prev_block->this_block_data +
                       alloc->prev_block->size) == alloc) {
    // Merge left
    alloc->prev_block->next_block = alloc->next_block;
    alloc->prev_block->size = alloc->prev_block->size + alloc->size + 32;
  }
}

void *LASAalloc::findFit(int size) {}

void *LASAalloc::split(block *target, int size) {}

/*
 *   >>>>>>  DO NOT CHANGE THIS SECTION  <<<<<<<
 *
 * brk()
 * Function to simulate the libc brk() function to allocate memory for a buffer
 *
 */

void *LASAalloc::brk(int size) {

  if (size != 0) {
    if (bufferBase == nullptr) {
      bufferBase = malloc(size);
      bufferSize = size;
    } else {
      cout << "buffer already locked \n";
      return 0;
    }
  }
  return bufferSize + (char*) bufferBase;
}