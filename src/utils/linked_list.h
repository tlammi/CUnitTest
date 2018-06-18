/**
  \file linked_list.h

  Header file for a linked list implementation used in CUnitTest

  \author tlammi
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
  \brief Struct for managing LinkedList elements
*/
struct LinkedNode {
  struct LinkedNode* next; ///< Pointer to next element
  struct LinkedNode* prev; ///< Pointer to previous element
  int bytes;  ///< Number of bytes in array val
  int val[0]; ///< Place holder for the value stored in the element
};

/**
  \brief Handle to LinkedList instance
*/
struct LinkedList {
  struct LinkedNode* head; ///< The first element in the list
  struct LinkedNode* current; ///< Current element (used for iterating)
  struct LinkedNode* tail; ///< The last element in the list
  int count; ///< Number of elements in the list
};

/**
  \brief Create a new instance of LinkedList

  \return A linked list handle
*/
struct LinkedList LinkedList_new(void);

/**
  \brief Destructor for a linked list

  \param handl - Reference to a LinkedList
    instance created with LinkedList_new()

*/
void LinkedList_destroy(struct LinkedList* handl);

/**
  \brief Get the number of elements in a LinkedList

  \param handl - Reference to a LinkedList
      instance created with LinkedList_new()

  \return The number of elements in the list
*/
int LinkedList_getCount(struct LinkedList* handl);

/**
  \brief Adds an element into the end of the LinkedList

  \param handl - Reference to a LinkedList
    instance created with LinkedList_new()
  \param val - Reference to value which is added into the LinkedList instance
  \param bytes - Number of bytes in value pointed by val

*/
void LinkedList_pushBack(struct LinkedList* handl, const void* val, int bytes);

/**
  \brief Adds an element int the front of the LinkedList

  \param handl - Reference to a LinkedList
    instance created with LinkedList_new()
  \param val - Reference to value-to-be-stored
  \param bytes - Number of bytes in value pointer by val
*/
void LinkedList_pushFront(struct LinkedList* handl, const void* val, int bytes);

/**
  \brief Get next element in the LinkedList by soft copy

  \param handl - Reference to a LinkedList
    instance created with LinkedList_new()
  \param val - Reference to a pointer which is set to point into the next value
    in the LinkedList
  \param bytes - Reference to a variable to which the number of bytes in
    val is stored

  \return 0 if successful, non-zero if the current element is the last element
    in the list
*/
int LinkedList_getNext(struct LinkedList* handl, void** val, int* bytes);

/**
  \brief Similar to LinkedList_getNext() but works from end to front
*/
int LinkedList_getPrev(struct LinkedList* handl, void** val, int* bytes);

/**
  \brief Get the current value in the list.

  Parameters work similarly to LinkedList_getNext()
*/
int LinkedList_getCurr(struct LinkedList* handl, void** val, int* bytes);

/**
  \brief Moves the "current" reference in LinkedList to the front of the list
*/
void LinkedList_setCurrToFront(struct LinkedList* handl);

/**
  \brief Same as LinkedList_setCurrToFront() but sets "current"
    to last element in the list
*/
void LinkedList_setCurrToBack(struct LinkedList* handl);

#endif
