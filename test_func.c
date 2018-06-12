#include "test_func.h"

#include "util.h"

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr){
  struct TestFunc tf = {
    .name = name,
    .test_func_ptr = funcptr,
    .failed = 0
  };
  return tf;
}

void TestFunc_exec(struct TestFunc* handl){
  printNote("\n"
            BOLD"##### executing function: %s #####\n"RESET
            "\n",
            handl->name);
  handl->test_func_ptr();
}

void TestFunc_registerFailure(struct TestFunc* handl){
  handl->failed++;
}

void TestFunc_setFailed(struct TestFunc* handl, int failed){
  handl->failed = failed;
}


int TestFunc_getFailed(struct TestFunc* handl){
  return handl->failed;
}



const char* TestFunc_getName(struct TestFunc* handl){
  return handl->name;
}
