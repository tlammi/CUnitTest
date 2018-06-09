#ifndef TEST_SET_DATABASE_H
#define TEST_SET_DATABASE_H

#include <stdlib.h>

#include "constants.h"
#include "test_func.h"

typedef void (*test_func)(void);

/*struct TestFunc{
  const char* name;
  test_func test_func_ptr;
  char failed;
};*/

/*struct TestSet {
  struct TestFunc test_funcs[C_UNIT_TEST_MAX_FUNCS_IN_SET];
  size_t test_func_count;
  const char* name;
  char failed;
};*/

struct TestSetDatabase{
  size_t set_count;
  struct TestSet test_sets[C_UNIT_TEST_MAX_TEST_SETS];
};

void CUnitTest_addTestSet(const char* test_set_name);


#define CUnitTest_addTestFunc(test_set_name, test_func_ptr)\
do{\
  __CUnitTest_addTestFunc(test_set_name, test_func_ptr, #test_func_ptr);\
}while(0)

void __CUnitTest_addTestFunc(const char* test_set_name,
                test_func funcptr, const char* func_name);
void CUnitTest_execute(void);


void __CUnitTest_registerFailure();

const char* __CUnitTest_getCurrentSet();


#endif
