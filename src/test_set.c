#include "test_set.h"
#include "print.h"

#include <string.h>

struct TestSet TestSet_newTestSet(const char* name){
  struct TestSet ts;
  ts.list = LinkedList_new();
  ts.name = name;
  ts.failed = 0;

  return ts;
}


void TestSet_destroy(struct TestSet* handl){

}

void TestSet_addTestFunc(struct TestSet* handl, const char* funcname, test_func funcptr){
  if(funcptr == NULL){
    printErr("funcptr cannot be NULL\n");
    return;
  }
  if(handl == NULL){
    printErr("handl cannot be NULL\n");
    return;
  }
  struct TestFunc tf = TestFunc_newTestFunc(funcname,funcptr);
  LinkedList_pushBack(&handl->list, (void*)&tf, sizeof(tf));
}

void TestSet_exec(struct TestSet* handl){
  /*printNote(BOLD"####################################################\n"
            "# executing set: %s\n"
            "####################################################\n\n"RESET,
            handl->name);*/

  struct TestFunc* func;
  int size;
  int ret_val;
  LinkedList_setCurrToFront(&handl->list);
  ret_val = LinkedList_getCurr(&handl->list, (void**)&func, &size);

  while(ret_val == 0){
    TestFunc_exec(func);
    ret_val = LinkedList_getNext(&handl->list, (void**)&func, &size);
  }
}

const char* TestSet_getName(struct TestSet* handl){
  return handl->name;
}


void TestSet_registerFailure(struct TestSet* handl, const char* info_str){
  struct TestFunc *current_func;
  int size, ret_val;

  ret_val = LinkedList_getCurr(&handl->list, (void**)&current_func, &size);

  if(ret_val == 0){
    if(TestFunc_getFailed(current_func) == 0){
      handl->failed++;
    }

    TestFunc_registerFailure(current_func, info_str);
  }
  /*if(TestFunc_getFailed(&handl->test_funcs[handl->current_test_func_index]) == 0){
    handl->failed++;
  }

  TestFunc_registerFailure(&handl->test_funcs[handl->current_test_func_index], info_str);
  */
}

void TestSet_setFailed(struct TestSet* handl, int failed){
  /*if(handl == NULL) {
    printErr("handl cannot be NULL\n");
    return;
  }

  handl->failed = failed;
  TestFunc_setFailed(&handl->test_funcs[handl->current_test_func_index], 1);*/
}

int TestSet_getFailed(struct TestSet* handl){
  if(handl == NULL){
    printErr("handl cannot be null");
    return -1;
  }

  return handl->failed;
}


void TestSet_printFailedFunctions(struct TestSet* handl){
  LinkedList_setCurrToFront(&handl->list);

  struct TestFunc* func;
  int size, ret_val;
  printNote("\t\tExecuted functions: %d\n",LinkedList_getCount(&handl->list));
  printOK("\t\tFunctions ok: %d\n", LinkedList_getCount(&handl->list) - handl->failed);
  printErr("\t\tFunctions failed: %d\n", handl->failed);
  printNote("\t\tFailed Test functions:\n");

  ret_val = LinkedList_getCurr(&handl->list, (void**)&func, &size);
  while(ret_val == 0){
    if(TestFunc_getFailed(func)){
      printErr("\t\t\t%s:\n",TestFunc_getName(func));
    }
    TestFunc_printFailedAsserts(func);
    ret_val = LinkedList_getNext(&handl->list, (void**)&func, &size);
  }

}
