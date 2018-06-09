#include "c_unit_test.h"

#include "test_set.h"
#include "test_func.h"

#include "util.h"

#include <string.h>

struct TestSetDatabase{
  int set_count;
  int current_set_index;
  struct TestSet test_sets[C_UNIT_TEST_MAX_TEST_SETS];
};

struct TestSetDatabase gtsdb = {
  .set_count = 0,
  .current_set_index = 0
};

void CUnitTest_addTestSet(const char* test_set_name){
  if(gtsdb.set_count == C_UNIT_TEST_MAX_TEST_SETS){
    printErr("Error: too many test sets.\n");
    return;
  }
  struct TestSet ts = TestSet_newTestSet(test_set_name);

  gtsdb.test_sets[gtsdb.set_count] = ts;
  gtsdb.set_count++;

}

void __CUnitTest_addTestFunc(const char* test_set_name,
                test_func funcptr, const char* func_name){
  if(gtsdb.set_count == 0){
    printErr("No registered sets\n");
    return;
  }
  if(strcmp(test_set_name, TestSet_getName(&gtsdb.test_sets[gtsdb.set_count-1]))){
    printErr("Functions currently have to be added to latest set\n");
    return;
  }

  TestSet_addTestFunc(&gtsdb.test_sets[gtsdb.set_count-1], func_name, funcptr);

}

void CUnitTest_execute(void){

  printNote(BOLD
            "####################################################\n"
            "Executing tests\n"
            "####################################################\n"
            RESET);

  for(gtsdb.current_set_index = 0; gtsdb.current_set_index<gtsdb.set_count; gtsdb.current_set_index++){
    TestSet_exec(&gtsdb.test_sets[gtsdb.current_set_index]);
  }

  printNote(BOLD
            "###################################################\n"
            "Test Summary\n"
            "###################################################\n"
            RESET);
  printNote("Failed test sets and functions:\n");
  int i;
  for(i=0; i<gtsdb.set_count; i++){
    if(TestSet_getFailed(&gtsdb.test_sets[i])){
      printErr("%s\n",TestSet_getName(&gtsdb.test_sets[i]))
      TestSet_printFailedFunctions(&gtsdb.test_sets[i]);
    }
  }

}


void __CUnitTest_registerFailure(){
  TestSet_setFailed(&gtsdb.test_sets[gtsdb.current_set_index], 1);
}
