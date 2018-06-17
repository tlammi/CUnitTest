#include "linked_list.h"
#include "print.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct LinkedList LinkedList_new(void){
  struct LinkedList l = {
    .head = NULL,
    .current = NULL,
    .tail = NULL,
    .count = 0
  };
  return l;
}

void LinkedList_destroy(struct LinkedList* handl){
  if(handl == NULL) return;
  struct LinkedNode* ptr = handl->head;
  while(ptr->next != NULL){
    ptr = ptr->next;
    free(ptr->prev);
  }
  free(ptr);
}

int LinkedList_getCount(struct LinkedList* handl){
  return handl->count;
}

void LinkedList_pushBack(struct LinkedList* handl, const void* val, int bytes){


  struct LinkedNode* ptr = malloc(sizeof(struct LinkedNode)+bytes);

  memcpy(&ptr->val, val, bytes);
  ptr->bytes = bytes;
  ptr->next = NULL;
  if(handl->tail != NULL){
    handl->tail->next = ptr;
    ptr->prev = handl->tail;
    handl->tail = ptr;
  } else {
    ptr->prev = NULL;
    handl->head = ptr;
    handl->tail = ptr;
    handl->current = ptr;
  }

  handl->count++;
}

void LinkedList_pushFront(struct LinkedList* handl, const void* val, int bytes){
  struct LinkedNode* ptr = malloc(sizeof(struct LinkedNode)+bytes);
  memcpy(ptr->val, val, bytes);
  ptr->bytes = bytes;
  ptr->prev = NULL;

  if(handl->head != NULL){
    handl->head->prev = ptr;
    ptr->next = handl->head;
    handl->head = ptr;
  } else {
    ptr->next = NULL;
    handl->head = ptr;
    handl->tail = ptr;
    handl->current = ptr;
  }
  handl->count++;
}

int LinkedList_getNext(struct LinkedList* handl, void** val, int* bytes){
  if(handl->current == handl->tail) return -1;
  handl->current = handl->current->next;
  *val = &handl->current->val;
  *bytes = handl->current->bytes;
  return 0;
}
int LinkedList_getPrev(struct LinkedList* handl, void** val, int* bytes){
  if(handl->current == handl->head) return -1;
  handl->current = handl->current->prev;
  *val = &handl->current->val;
  *bytes = handl->current->bytes;
  return 0;
}



int LinkedList_getCurr(struct LinkedList* handl, void** val, int* bytes){
  if(handl->current == NULL) return -1;
  *val = &handl->current->val;
  *bytes = handl->current->bytes;
  return 0;
}



void LinkedList_setCurrToFront(struct LinkedList* handl){
  handl->current = handl->head;
}

void LinkedList_setCurrToBack(struct LinkedList* handl){
  handl->current = handl->tail;
}
