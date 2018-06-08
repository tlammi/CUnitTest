#ifndef ASSERTIONS_H
#define ASSERTIONS_H

#include <stdio.h>
#include <string.h>

#include "util.h"

/*
 * \brief Assert a boolean statement and log error if fail
 *
*/
#define CUnitTest_assert(assertion) do{\
  printNote("Testing CUnitTest_assert(" #assertion")...\n");                                       \
  if(!(assertion)){                                                           \
    CUnitTest_logAssertError(__FILE__, __FUNCTION__, __LINE__, #assertion);\
    __CUnitTest_registerFailure();   \
  } else {                                                                    \
    printOK("Assertion" BOLD " ok\n" RESET);                                                 \
  }                                                                           \
}while(0)

#define CUnitTest_assertEqual(val1, val2) do{\
  printNote("Testing CUnitTest_assertEqual("#val1", " #val2")...\n");\
  if(val1 != val2){\
    CUnitTest_logAssertEqualError(__FILE__, __FUNCTION__, __LINE__, val1, val2);\
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0)

#define CUnitTest_assertNotEqual(val1, val2)do{\
  printNote("Testing CUnitTest_assertNotEqual("#val1", " #val2")...\n");\
  if(val1 == val2){\
    CUnitTest_logAssertNotEqualError(__FILE__, __FUNCTION__, __LINE__, val1, val2);\
  } else {\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0)

#define CUnitTest_assertStrEqual(str1, str2)do{\
  printNote("Testing CUnitTest_assertStrEqual("#str1", "#str2")...\n");\
  if(strcmp(str1, str2)){\
    CUnitTest_logAssertStrEqualError(__FILE__, __FUNCTION__, __LINE__, str1, str2);\
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0);



void CUnitTest_logAssertError(const char* file, const char* func, const int line, const char* assertion);

void CUnitTest_logAssertEqualError(const char* file, const char* func,
                                   const int line, const int val1, const int val2);

void CUnitTest_logAssertNotEqualError(const char* file, const char* func,
                                   const int line, const int val1, const int val2);

void CUnitTest_logAssertStrEqualError(const char* file, const char* func,
                                   const int line, const char* str1, const char* str2);
#endif
