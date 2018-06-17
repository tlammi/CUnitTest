#include "c_unit_test_priv.h"
#include "print.h"

#include <string.h>

static inline void printPrefix(const char* file,
                               const char* func,
                               const int line){
  printErr("Assertion failure:\n\tfile: %s\n\tfunc: %s\n\tline: %d\n\t",
          file, func, line);
}


void __CUnitTest_logAssertError(const char* file,
                              const char* func,
                              const int line,
                              const char* assertion){
  char buffer[C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN];
  snprintf(buffer, C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN, "CUnitTest_assert(%s)", assertion);
  __CUnitTest_registerFailure(buffer);
}

void __CUnitTest_logAssertEqualError(const char* file, const char* func,
                                   const int line, const int val1,
                                   const int val2, const char* val1str, const char* val2str){
  char buffer[C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN];
  snprintf(buffer, C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN, "CUnitTest_assertEqual(%s, %s), values were %d and %d", val1str, val2str, val1, val2);
  __CUnitTest_registerFailure(buffer);
}

void __CUnitTest_logAssertNotEqualError(const char* file, const char* func,
                                   const int line, const int val,
                                   const char* val1str, const char* val2str){
  char buffer[C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN];
  snprintf(buffer, C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN, "CUnitTest_assertNotEqual(%s, %s), value was %d", val1str, val2str, val);
  __CUnitTest_registerFailure(buffer);
}

void __CUnitTest_logAssertStrEqualError(const char* file, const char* func,
                                   const int line, const char* str1,
                                   const char* str2, const char* str1str, const char* str2str){
  char buffer[C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN];
  snprintf(buffer, C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN, "CUnitTest_assertStrEqual(%s, %s), values were: \"%s\" and \"%s\"", str1str, str2str, str1, str2);
  __CUnitTest_registerFailure(buffer);
}



void __CUnitTest_assertFunc(const char* file, const char* func, int line, char assertion, const char* assertion_str){
  if(!(assertion)){
    __CUnitTest_logAssertError(file, func, line, assertion_str);
  }
}

void __CUnitTest_assertEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str){
  if(val1 != val2){
    __CUnitTest_logAssertEqualError(file, func, line, val1, val2, val1str, val2str);
  }
}

void __CUnitTest_assertNotEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str){
  if(val1 == val2){
    __CUnitTest_logAssertNotEqualError(file, func, line, val1, val1str, val2str);
  }
}


void __CUnitTest_assertStrEqualFunc(const char* file, const char* func, int line, const char* str1, const char* str2, const char* str1str, const char* str2str){
  if(strcmp(str1, str2)){
    __CUnitTest_logAssertStrEqualError(file, func, line, str1, str2, str1str, str2str);
  }
}
