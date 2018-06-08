#include "test_set_database.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

struct TestSetDatabase gTestSet_database = {
  .set_count = 0
};


struct TestSet* gpCurrentTestSet;
struct TestFunc* gpCurrentTestFunc;

void CUnitTest_addTestSet(const char* test_set_name){

  if(gTestSet_database.set_count < C_UNIT_TEST_MAX_TEST_SETS){
    struct TestSet new_set;
    memset(&new_set, 0, sizeof(new_set));
    new_set.name = test_set_name;
    new_set.test_func_count = 0;

    gTestSet_database.test_sets[gTestSet_database.set_count] = new_set;
    gTestSet_database.set_count++;

  } else {
    printf("Too many test sets!\n");

  }

}

void __CUnitTest_addTestFunc(const char* test_set_name, test_func funcptr,
                             const char* funcname){
  size_t set_count = gTestSet_database.set_count;
  if(set_count == 0){
    printf("Error: No registered sets\n");
    return;
  }
  struct TestSet* test_set = &gTestSet_database.test_sets[set_count-1];


  if(strcmp(test_set->name, test_set_name)){
    printf("Error: Currently only adding functions to latest set is enabled\n");
    return;
  }

  if(test_set->test_func_count < C_UNIT_TEST_MAX_FUNCS_IN_SET){
    test_set->test_funcs[test_set->test_func_count].test_func_ptr = funcptr;
    test_set->test_funcs[test_set->test_func_count].name = funcname;
    test_set->test_funcs[test_set->test_func_count].failed = 0;
    test_set->test_func_count++;
  } else{
    printf("Too many functions in set!\n");
  }

}

static void printConclusion(){
  printNote("\n\n"
            "#############################################\n"
            "# Printing conclusion\n"
            "#############################################\n")
  struct TestSet* testsets = gTestSet_database.test_sets;
  size_t set_count = gTestSet_database.set_count;
  int i, ii;
  for(i=0; i<set_count; i++){
    if(testsets[i].failed){
      printErr("Failed test set: %s\n",testsets[i].name);
      size_t func_count = testsets[i].test_func_count;
      struct TestFunc* funcs = testsets[i].test_funcs;

      for(ii=0; ii<func_count; ii++){
        if(funcs[ii].failed){
          printErr("\tFailed test function: %s\n",funcs[ii].name);
        }
      }
    }
  }

}

void CUnitTest_execute(void){

  size_t set_count = gTestSet_database.set_count;
  int i;

  for(i=0;i<set_count;i++){
    struct TestSet* test_set = &gTestSet_database.test_sets[i];
    printNote(BOLD"####################################################\n"
              "# executing set: %s\n"
              "####################################################\n\n"RESET,
               test_set->name);

    gpCurrentTestSet = test_set;
    int ii;
    size_t func_count = test_set->test_func_count;
    for(ii=0;ii<func_count;ii++){
      printNote("\n"
                BOLD"##### executing function: %s #####\n"RESET
                "\n",
                test_set->test_funcs[ii].name);
      gpCurrentTestFunc = &test_set->test_funcs[ii];
      test_set->test_funcs[ii].test_func_ptr();
    }
  }

  printConclusion();
}


void __CUnitTest_registerFailure(){
  gpCurrentTestFunc->failed = 1;
  gpCurrentTestSet->failed = 1;
}



const char* __CUnitTest_getCurrentSet(){
 return gpCurrentTestSet->name;
}
