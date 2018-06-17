#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct LinkedNode {
  struct LinkedNode* next;
  struct LinkedNode* prev;
  int bytes;
  int val[0];
};

struct LinkedList {
  struct LinkedNode* head;
  struct LinkedNode* current;
  struct LinkedNode* tail;
  int count;
};

struct LinkedList LinkedList_new(void);
void LinkedList_destroy(struct LinkedList* handl);

int LinkedList_getCount(struct LinkedList* handl);

void LinkedList_pushBack(struct LinkedList* handl, const void* val, int bytes);

void LinkedList_pushFront(struct LinkedList* handl, const void* val, int bytes);

int LinkedList_getNext(struct LinkedList* handl, void** val, int* bytes);
int LinkedList_getPrev(struct LinkedList* handl, void** val, int* bytes);
int LinkedList_getCurr(struct LinkedList* handl, void** val, int* bytes);

void LinkedList_setCurrToFront(struct LinkedList* handl);
void LinkedList_setCurrToBack(struct LinkedList* handl);

#endif
