#include "test_func.h"
#include "util.h"

#include <string.h>

struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr){
  struct TestFunc tf = {
    .name = name,
    .test_func_ptr = funcptr,
    .failed = 0
  };
  memset(tf.failed_assertion_infos, 0,
    C_UNIT_TEST_MAX_ASSERTS_IN_FUNC*C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN);
  return tf;
}

void TestFunc_exec(struct TestFunc* handl){
  printNote("\n"
            BOLD"##### executing function: %s #####\n"RESET
            "\n",
            handl->name);
  handl->test_func_ptr();
}

void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str){
  if(handl != NULL && handl->failed < C_UNIT_TEST_MAX_ASSERTS_IN_FUNC){
    memcpy(handl->failed_assertion_infos[handl->failed],
      info_str, C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN);
    handl->failed++;
  }
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

void TestFunc_printFailedAsserts(struct TestFunc* handl){
  for(int i = 0; i< handl->failed; i++){
    printErr("%s\n",&handl->failed_assertion_infos[i][0]);
  }
}
