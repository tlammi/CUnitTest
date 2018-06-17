#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include "constants.h"
#include "linked_list.h"


typedef void (*test_func)(void);

struct TestFunc{
  const char* name;
  test_func test_func_ptr;
  int failed;
  struct LinkedList list;
};

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr);

void TestFunc_destroy(struct TestFunc* handl);

void TestFunc_exec(struct TestFunc* handl);

void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str);

int TestFunc_getFailed(struct TestFunc* handl);

const char* TestFunc_getName(struct TestFunc* handl);

void TestFunc_printFailedAsserts(struct TestFunc* handl);

#endif
