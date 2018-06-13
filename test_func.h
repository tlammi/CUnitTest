#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include "constants.h"

typedef void (*test_func)(void);

struct TestFunc{
  const char* name;
  test_func test_func_ptr;
  int failed;
  char failed_assertion_infos[C_UNIT_TEST_MAX_ASSERTS_IN_FUNC][C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN];
};

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr);

void TestFunc_exec(struct TestFunc* handl);

void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str);

void TestFunc_setFailed(struct TestFunc* handl, int failed);

int TestFunc_getFailed(struct TestFunc* handl);

const char* TestFunc_getName(struct TestFunc* handl);

void TestFunc_printFailedAsserts(struct TestFunc* handl);

#endif
