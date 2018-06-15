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
  printPrefix(file, func, line);
  printErr("assertion: %s\n",assertion);
  __CUnitTest_registerFailure("1");
}

void __CUnitTest_logAssertEqualError(const char* file, const char* func,
                                   const int line, const int val1,
                                   const int val2){
  printPrefix(file, func, line);
  printErr("first value: %d\n\tsecond value: %d\n",val1, val2);
  __CUnitTest_registerFailure("2");
}

void __CUnitTest_logAssertNotEqualError(const char* file, const char* func,
                                   const int line, const int val1,
                                   const int val2){
  (void)val1;
  (void)val2;
  printPrefix(file, func, line);
  printErr("Values were equal\n");
  __CUnitTest_registerFailure("3");
}

void __CUnitTest_logAssertStrEqualError(const char* file, const char* func,
                                   const int line, const char* str1,
                                   const char* str2){
  printPrefix(file, func, line);
  printErr("first str: %s\n\tsecond str: %s\n",str1, str2);
  __CUnitTest_registerFailure("4");
}



void __CUnitTest_assertFunc(const char* file, const char* func, int line, char assertion, const char* assertion_str){
  printNote("Testing CUnitTest_assert(%s)...\n",assertion_str);
  if(!(assertion)){
    __CUnitTest_logAssertError(file, func, line, assertion_str);
  } else {
    printOK("Assertion" BOLD " ok\n" RESET);
  }
}

void __CUnitTest_assertEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str){
  printNote("Testing CUnitTest_assertEqual(%s, %s)...\n", val1str, val2str);
  if(val1 != val2){\
    __CUnitTest_logAssertEqualError(file, func, line, val1, val2);
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}

void __CUnitTest_assertNotEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str){
  printNote("Testing CUnitTest_assertNotEqual(%s,  %s)...\n",
    val1str, val2str);
  if(val1 == val2){
    __CUnitTest_logAssertNotEqualError(file, func, line, val1, val2);
  } else {
    printOK("Assertion" BOLD " ok\n" RESET);
  }
}


void __CUnitTest_assertStrEqualFunc(const char* file, const char* func, int line, const char* str1, const char* str2){
  printNote("Testing CUnitTest_assertStrEqual(%s, %s)...\n", str1, str2);\
  if(strcmp(str1, str2)){\
    __CUnitTest_logAssertStrEqualError(file, func, line, str1, str2);\
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}
