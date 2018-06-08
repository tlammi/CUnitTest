#include "test_set_database.h"

#include <stdio.h>
#include <string.h>

struct TestSetDatabase gTestSet_database = {
  .set_count = 0
};


struct TestSet* gpCurrentTestSet;

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

void CUnitTest_addTestFunc(const char* test_set_name, test_func funcptr){
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
    test_set->test_funcs[test_set->test_func_count] = funcptr;
    test_set->test_func_count++;
  } else{
    printf("Too many functions in set!\n");
  }

}


void CUnitTest_execute(void){

  size_t set_count = gTestSet_database.set_count;
  int i;

  for(i=0;i<set_count;i++){
    struct TestSet test_set = gTestSet_database.test_sets[i];
    gpCurrentTestSet = &test_set;
    int ii;
    size_t func_count = test_set.test_func_count;
    for(ii=0;ii<func_count;ii++){
      test_set.test_funcs[ii]();
    }
  }


}




const char* __CUnitTest_getCurrentSet(){
 return gpCurrentTestSet->name;
}
