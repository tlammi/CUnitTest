#include "test_set.h"
#include "util.h"

#include <string.h>

struct TestSet TestSet_newTestSet(const char* name){
  struct TestSet ts;
  memset(&ts, 0, sizeof(ts));
  ts.test_func_count = 0;
  ts.name = name;
  ts.current_test_func_index = 0;
  ts.failed = 0;

  return ts;
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
  if(handl->test_func_count >= C_UNIT_TEST_MAX_FUNCS_IN_SET){
    printErr("Too many functions in a set\n");
    return;
  }
  handl->test_funcs[handl->test_func_count] = TestFunc_newTestFunc(funcname, funcptr);
  handl->test_func_count++;

}

void TestSet_exec(struct TestSet* handl){
  printNote(BOLD"####################################################\n"
            "# executing set: %s\n"
            "####################################################\n\n"RESET,
            handl->name);

  for(handl->current_test_func_index=0;
      handl->current_test_func_index<handl->test_func_count;
      handl->current_test_func_index++){
    TestFunc_exec(&handl->test_funcs[handl->current_test_func_index]);
  }
}

const char* TestSet_getName(struct TestSet* handl){
  return handl->name;
}

void TestSet_setFailed(struct TestSet* handl, char failed){
  if(handl == NULL) {
    printErr("handl cannot be NULL\n");
    return;
  }

  handl->failed = failed;
  TestFunc_setFailed(&handl->test_funcs[handl->current_test_func_index], 1);
}

char TestSet_getFailed(struct TestSet* handl){
  if(handl == NULL){
    printErr("handl cannot be null");
    return -1;
  }

  return handl->failed;
}

void TestSet_printFailedFunctions(struct TestSet* handl){
  int i;
  for(i=0; i<handl->test_func_count; i++){
    printErr("\t%s\n",TestFunc_getName(&handl->test_funcs[i]));
  }
}