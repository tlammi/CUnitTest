#include "test_func.h"
#include "print.h"

#include <string.h>

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr){
  struct TestFunc tf = {
    .name = name,
    .test_func_ptr = funcptr,
    .failed = 0
  };
  tf.list = LinkedList_new();
  return tf;
}

void TestFunc_destroy(struct TestFunc* handl){
  LinkedList_destroy(&handl->list);
}


void TestFunc_exec(struct TestFunc* handl){
  printNote(BOLD"executing %s...\n"RESET,
            handl->name);
  handl->test_func_ptr();
  if(!handl->failed){
    printOK(BOLD"%s passed\n"RESET, handl->name);
  } else {
    printErr(BOLD"%s failed\n"RESET, handl->name);
  }
}

void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str){
  if(handl != NULL){
    LinkedList_pushBack(&handl->list, info_str, strlen(info_str));
    handl->failed++;
  }
}

void TestFunc_setFailed(struct TestFunc* handl, int failed){
  handl->failed = failed;
}


int TestFunc_getFailed(struct TestFunc* handl){
  return handl->failed;
}



const char* TestFunc_getName(struct TestFunc* handl){
  return handl->name;
}

void TestFunc_printFailedAsserts(struct TestFunc* handl){
  char* info_str;
  int str_len;
  int ret_val;
  ret_val = LinkedList_getCurr(&handl->list, (void**)&info_str, &str_len);
  while(ret_val == 0){
    printErr("\t\t\t\t%s\n", info_str);
    ret_val = LinkedList_getNext(&handl->list, (void**)&info_str, &str_len);
  }
}
