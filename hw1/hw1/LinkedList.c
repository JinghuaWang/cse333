/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 project sequence (333proj12).
 *
 *  333proj12 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  333proj12 is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj12.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "CSE333.h"
#include "LinkedList.h"
#include "LinkedList_priv.h"

LinkedList AllocateLinkedList(void) {
  // allocate the linked list record
  LinkedList ll = (LinkedList) malloc(sizeof(LinkedListHead));
  if (ll == NULL) {
    // out of memory
    return (LinkedList) NULL;
  }

  // Step 1.
  // initialize the newly allocated record structure
  ll->num_elements = 0;
  ll->head = NULL;
  ll->tail = NULL;

  // return our newly minted linked list
  return ll;
}

void FreeLinkedList(LinkedList list,
                    LLPayloadFreeFnPtr payload_free_function) {
  // defensive programming: check arguments for sanity.
  Verify333(list != NULL);
  Verify333(payload_free_function != NULL);

  // Step 2.
  // sweep through the list and free all of the nodes' payloads as
  // well as the nodes themselves
  while (list->head != NULL) {
    // Set curr ptr to head and shift head to next
    LinkedListNodePtr curr = list->head;
    list->head = list->head->next;

    // free payload
    payload_free_function(curr->payload);

    // free node
    free(curr);

    // subtract the number of elements by 1
    list->num_elements--;
  }

  // free the list record
  free(list);
}

HWSize_t NumElementsInLinkedList(LinkedList list) {
  // defensive programming: check argument for safety.
  Verify333(list != NULL);
  return list->num_elements;
}

bool PushLinkedList(LinkedList list, LLPayload_t payload) {
  // defensive programming: check argument for safety. The user-supplied
  // argument can be anything, of course, so we need to make sure it's
  // reasonable (e.g., not NULL).
  Verify333(list != NULL);

  // allocate space for the new node.
  LinkedListNodePtr ln =
    (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (ln == NULL) {
    // out of memory
    return false;
  }

  // set the payload
  ln->payload = payload;

  if (list->num_elements == 0) {
    // degenerate case; list is currently empty
    Verify333(list->head == NULL);  // debugging aid
    Verify333(list->tail == NULL);  // debugging aid
    ln->next = ln->prev = NULL;
    list->head = list->tail = ln;
    list->num_elements = 1U;
    return true;
  }

  // STEP 3.
  // typical case; list has >=1 elements
  if (list->num_elements >= 1) {
    list->head->prev = ln;
    ln->next = list->head;
    ln->prev = NULL;
    list->head = ln;
    list->num_elements++;

    return true;
  }

  // return success
  return true;
}

bool PopLinkedList(LinkedList list, LLPayload_t *payload_ptr) {
  // defensive programming.
  Verify333(payload_ptr != NULL);
  Verify333(list != NULL);

  // Step 4: implement PopLinkedList.  Make sure you test for
  // and empty list and fail.  If the list is non-empty, there
  // are two cases to consider: (a) a list with a single element in it
  // and (b) the general case of a list with >=2 elements in it.
  // Be sure to call free() to deallocate the memory that was
  // previously allocated by PushLinkedList().

  // Test for empty list
  if (list->num_elements == 0) {
    return false;
  } 
  // Single element case
  else if (list->num_elements == 1) {
    *payload_ptr = list->head->payload;
    free(list->head);
    list->head = list->tail = NULL;
    list->num_elements--;
  }
  // >=2 element case
  else {
    *payload_ptr = list->head->payload;
    free(list->head);
    list->head = list->head->next;
    list->head->prev = NULL;
    list->num_elements--;
  }
  return true;
}

bool AppendLinkedList(LinkedList list, LLPayload_t payload) {
  // defensive programming: check argument for safety.
  Verify333(list != NULL);

  // Step 5: implement AppendLinkedList.  It's kind of like
  // PushLinkedList, but obviously you need to add to the end
  // instead of the beginning.

  // allocate space for the new node.
  LinkedListNodePtr ln =
    (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (ln == NULL) {
    // out of memory
    return false;
  }

  // Set the payload
  ln->payload = payload;

  if (list->num_elements == 0) {
                  // degenerate case; list is currently empty
                  Verify333(list->head == NULL);  // debugging aid
                  Verify333(list->tail == NULL);  // debugging aid
                  // ln->next = ln->prev = NULL;
                  // list->head = list->tail = ln;
                  // list->num_elements = 1U;
                  // return true;
    return PushLinkedList(list, payload);
  }

  // typical case; list has >=1 elements
  if (list->num_elements >= 1) {
    ln->next = NULL;
    list->tail->next = ln;
    ln->prev = list->tail;
    list->tail = ln;
    list->num_elements++;

    return true;
  }


  return true;
}

bool SliceLinkedList(LinkedList list, LLPayload_t *payload_ptr) {
  // defensive programming.
  Verify333(payload_ptr != NULL);
  Verify333(list != NULL);

  // Step 6: implement SliceLinkedList. (mostly copied from Step 4)

  // Test for empty list
  if (list->num_elements == 0) {
    return false;
  } 
  // Single element case
  else if (list->num_elements == 1) {
    *payload_ptr = list->head->payload;
    free(list->head);
    list->head = list->tail = NULL;
    list->num_elements--;
  }
  // >=2 element case
  else {
    *payload_ptr = list->tail->payload;
    // LinkedListNodePtr oldnode = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(list->tail);
    list->num_elements--;
  }

  return true;
}

void SortLinkedList(LinkedList list, unsigned int ascending,
                    LLPayloadComparatorFnPtr comparator_function) {
  Verify333(list != NULL);  // defensive programming
  if (list->num_elements < 2) {
    // no sorting needed
    return;
  }

  // we'll implement bubblesort! nice and easy, and nice and slow :)
  int swapped;
  do {
    LinkedListNodePtr curnode;

    swapped = 0;
    curnode = list->head;
    while (curnode->next != NULL) {
      int compare_result = comparator_function(curnode->payload,
                                               curnode->next->payload);
      if (ascending) {
        compare_result *= -1;
      }
      if (compare_result < 0) {
        // bubble-swap payloads
        LLPayload_t tmp;
        tmp = curnode->payload;
        curnode->payload = curnode->next->payload;
        curnode->next->payload = tmp;
        swapped = 1;
      }
      curnode = curnode->next;
    }
  } while (swapped);
}

LLIter LLMakeIterator(LinkedList list, int pos) {
  // defensive programming
  Verify333(list != NULL);
  Verify333((pos == 0) || (pos == 1));

  // if the list is empty, return failure.
  if (NumElementsInLinkedList(list) == 0U)
    return NULL;

  // OK, let's manufacture an iterator.
  LLIter li = (LLIter) malloc(sizeof(LLIterSt));
  if (li == NULL) {
    // out of memory!
    return NULL;
  }

  // set up the iterator.
  li->list = list;
  if (pos == 0) {
    li->node = list->head;
  } else {
    li->node = list->tail;
  }

  // return the new iterator
  return li;
}

void LLIteratorFree(LLIter iter) {
  // defensive programming
  Verify333(iter != NULL);
  free(iter);
}

bool LLIteratorHasNext(LLIter iter) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // Is there another node beyond the iterator?
  if (iter->node->next == NULL)
    return false;  // no

  return true;  // yes
}

bool LLIteratorNext(LLIter iter) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // Step 7: if there is another node beyond the iterator, advance to it,
  // and return true.

  // check for additional node
  if (iter->node->next != NULL) {
    // if it exists, advance to it
    iter->node = iter->node->next;
    return true;
  }

  // Nope, there isn't another node, so return failure.
  return false;
}

bool LLIteratorHasPrev(LLIter iter) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // Is there another node beyond the iterator?
  if (iter->node->prev == NULL)
    return false;  // no

  return true;  // yes
}

bool LLIteratorPrev(LLIter iter) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // Step 8:  if there is another node beyond the iterator, advance to it,
  // and return true.

  // check for previous node
  if (iter->node->prev != NULL) {
    // if it exists, advance
    iter->node = iter->node->prev;
    return true;
  }

  // Nope, so return failure.
  return false;
}

void LLIteratorGetPayload(LLIter iter, LLPayload_t *payload) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // set the return parameter.
  *payload = iter->node->payload;
}

bool LLIteratorDelete(LLIter iter,
                      LLPayloadFreeFnPtr payload_free_function) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // Step 9: implement LLIteratorDelete.  This is the most
  // complex function you'll build.  There are several cases
  // to consider:
  //
  // - degenerate case: the list becomes empty after deleting.
  // - degenerate case: iter points at head
  // - degenerate case: iter points at tail
  // - fully general case: iter points in the middle of a list,
  //                       and you have to "splice".
  //
  // Be sure to call the payload_free_function to free the payload
  // the iterator is pointing to, and also free any LinkedList
  // data structure element as appropriate.


  // free node payload (needed in all cases)
  payload_free_function(iter->node->payload);

  // degenerate case: the list becomes empty after deleting.
  if (iter->list->num_elements < 1) {
    return false;
  }
  else if (iter->list->num_elements == 1) {
    // free element
    free(iter->list->head);
    // set pointers to null
    iter->list->tail = iter->list->head = iter->node = NULL;
    // subtract num_elements
    iter->list->num_elements--;
    return false;
  }
  // degenerate case: iter points at head
  else if (iter->node == iter->list->head) {
    // move to new head
    iter->list->head = iter->list->head->next;
    // set prev to NULL
    iter->list->head->prev = NULL;
    free(iter->list->head);
    iter->node = iter->list->head;
    // subtract num_elements
    iter->list->num_elements--;
  }
  // degenerate case: iter points at tail
  else if (iter->node == iter->list->tail) {
    iter->list->tail = iter->list->tail->prev;
    iter->list->tail->next = NULL;
    free(iter->list->tail);
    iter->node = iter->list->tail;
    // subtract num_elements
    iter->list->num_elements--;
  }
  // fully general case: iter points in the middle of a list,
  //                       and you have to "splice".
  else {
    iter->node->prev->next = iter->node->next;
    iter->node->prev->next->prev = iter->node->prev;
    free(iter->node);
    iter->node = iter->node->prev->next;
    // subtract num_elements
    iter->list->num_elements--;
  }


  return true;
}

bool LLIteratorInsertBefore(LLIter iter, LLPayload_t payload) {
  // defensive programming
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // If the cursor is pointing at the head, use our
  // PushLinkedList function.
  if (iter->node == iter->list->head) {
    return PushLinkedList(iter->list, payload);
  }

  // General case: we have to do some splicing.
  LinkedListNodePtr newnode =
    (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (newnode == NULL)
    return false;  // out of memory

  newnode->payload = payload;
  newnode->next = iter->node;
  newnode->prev = iter->node->prev;
  newnode->prev->next = newnode;
  newnode->next->prev = newnode;
  iter->list->num_elements += 1;
  return true;
}
