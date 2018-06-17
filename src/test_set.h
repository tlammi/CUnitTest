#ifndef TEST_SET_H
#define TEST_SET_H

#include "constants.h"
#include "test_func.h"


struct TestSet {
  struct LinkedList list;
  const char* name;
  int failed;
};

struct TestSet TestSet_newTestSet(const char* name);

void TestSet_destroy(struct TestSet* handl);

void TestSet_addTestFunc(struct TestSet* handl, const char* funcname,
  test_func funcptr);

void TestSet_exec(struct TestSet* handl);

const char* TestSet_getName(struct TestSet* handl);

void TestSet_registerFailure(struct TestSet* handl, const char* info_str);

int TestSet_getFailed(struct TestSet* handl);

void TestSet_printFailedFunctions(struct TestSet* handl);

#endif
