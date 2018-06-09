#ifndef TEST_SET_H
#define TEST_SET_H

#include "constants.h"
#include "test_func.h"


struct TestSet {
  struct TestFunc test_funcs[C_UNIT_TEST_MAX_FUNCS_IN_SET];
  int test_func_count;
  int current_test_func_index;
  const char* name;
  char failed;
};

struct TestSet TestSet_newTestSet(const char* name);

void TestSet_addTestFunc(struct TestSet* handl, const char* funcname, test_func funcptr);

void TestSet_exec(struct TestSet* handl);

const char* TestSet_getName(struct TestSet* handl);

void TestSet_setFailed(struct TestSet* handl, char failed);

char TestSet_getFailed(struct TestSet* handl);

void TestSet_printFailedFunctions(struct TestSet* handl);

#endif
