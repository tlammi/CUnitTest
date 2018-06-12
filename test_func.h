#ifndef TEST_FUNC_H
#define TEST_FUNC_H

typedef void (*test_func)(void);

struct TestFunc{
  const char* name;
  test_func test_func_ptr;
  int failed;
};

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr);

void TestFunc_exec(struct TestFunc* handl);

void TestFunc_registerFailure(struct TestFunc* handl);

void TestFunc_setFailed(struct TestFunc* handl, int failed);

int TestFunc_getFailed(struct TestFunc* handl);

const char* TestFunc_getName(struct TestFunc* handl);

#endif
