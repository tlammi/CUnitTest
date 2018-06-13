#include "c_unit_test.h"

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
