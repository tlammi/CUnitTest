#ifndef TEST_SET_DATABASE_H
#define TEST_SET_DATABASE_H

#include <stdlib.h>

#include "constants.h"
#include "test_set.h"


typedef void (*test_func)(void);


struct TestSet {
  test_func test_funcs[C_UNIT_TEST_MAX_FUNCS_IN_SET];
  size_t test_func_count;
  const char* name;
};

struct TestSetDatabase{
  size_t set_count;
  struct TestSet test_sets[C_UNIT_TEST_MAX_TEST_SETS];
  unsigned char sorted;
};

void CUnitTest_addTestSet(const char* test_set_name);
void CUnitTest_addTestFunc(const char* test_set_name, test_func funcptr);
void CUnitTest_execute(void);

#endif
