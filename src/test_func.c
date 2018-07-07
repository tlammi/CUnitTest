#include "test_func.h"
#include "print.h"

#include <string.h>

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr){
  struct TestFunc tf = {
    .name = name,
    .test_func_ptr = funcptr,
    .failed = 0,
    .succeeded = 0
  };
  tf.failed_list = LinkedList_new();
  tf.info_list = LinkedList_new();
  return tf;
}

void TestFunc_destroy(struct TestFunc* handl){
  LinkedList_destroy(&handl->info_list);
  LinkedList_destroy(&handl->failed_list);
}


void TestFunc_exec(struct TestFunc* handl){
  printNote(BOLD"executing %s...\n"RESET,
            handl->name);
  handl->test_func_ptr();
  if(!LinkedList_getCount(&handl->info_list)){
    printOK(BOLD"%s passed\n"RESET, handl->name);
  } else {
    printErr(BOLD"%s failed\n"RESET, handl->name);
  }
}

void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str){
  if(handl != NULL){
    LinkedList_pushBack(&handl->info_list, info_str, strlen(info_str));
    int tru = 1;
    LinkedList_pushBack(&handl->failed_list, (const void*)&tru, sizeof(1));
    handl->failed++;
  }
}

void TestFunc_registerOk(struct TestFunc* handl, const char* info_str){
  if(handl != NULL){
    LinkedList_pushBack(&handl->info_list, info_str, strlen(info_str));
    int fal = 0;
    LinkedList_pushBack(&handl->failed_list, (const void*)&fal, sizeof(0));
    handl->succeeded++;
  }
}


int TestFunc_getFailed(struct TestFunc* handl){
  return handl->failed;
}

int TestFunc_getSucceeded(struct TestFunc* handl){
  return handl->succeeded;
}


const char* TestFunc_getName(struct TestFunc* handl){
  return handl->name;
}

void TestFunc_printFailedAsserts(struct TestFunc* handl){
  char* info_str;
  int str_len;
  int ret_val;
  ret_val = LinkedList_getCurr(&handl->info_list, (void**)&info_str, &str_len);
  while(ret_val == 0){
    printErr("\t\t\t\t%s\n", info_str);
    ret_val = LinkedList_getNext(&handl->info_list, (void**)&info_str, &str_len);
  }
}

struct LinkedList TestFunc_getFailedList(struct TestFunc* handl){
  return handl->failed_list;
}
struct LinkedList TestFunc_getInfoList(struct TestFunc* handl){
  return handl->info_list;
}
