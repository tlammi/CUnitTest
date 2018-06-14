#ifndef C_UNIT_TEST_H
#define C_UNIT_TEST_H


#include <string.h>

#include "print.h"

/*
 * \brief Test function template
*/
typedef void(*test_func)(void);

/*
 * \brief Add a test set into test database
*/
void CUnitTest_addTestSet(const char* test_set_name);

/*
 * \brief Add a test function into a test set
 * \todo Functions can currently be added only into lastly added test set
*/
#define CUnitTest_addTestFunc(test_set_name, test_func_ptr)\
do{\
  __CUnitTest_addTestFunc(test_set_name, test_func_ptr, #test_func_ptr);\
}while(0)

/*
 * \brief Execute regitered tests
*/
void CUnitTest_execute(void);




/*
 * \brief Assert a boolean statement and log error if fail
 *
*/
#define CUnitTest_assert(assertion) do{\
  printNote("Testing CUnitTest_assert(" #assertion")...\n");                                       \
  if(!(assertion)){                                                           \
    __CUnitTest_logAssertError(__FILE__, __FUNCTION__, __LINE__, #assertion);\
  } else {                                                                    \
    printOK("Assertion" BOLD " ok\n" RESET);                                                 \
  }                                                                           \
}while(0)

/*
 * \brief Assert that values (integer) are equal
*/
#define CUnitTest_assertEqual(val1, val2) do{\
  printNote("Testing CUnitTest_assertEqual("#val1", " #val2")...\n");\
  if(val1 != val2){\
    __CUnitTest_logAssertEqualError(__FILE__, __FUNCTION__, __LINE__, val1, val2);\
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0)

/*
 * \brief Assert that values are non-equal
*/
#define CUnitTest_assertNotEqual(val1, val2)do{\
  printNote("Testing CUnitTest_assertNotEqual("#val1", " #val2")...\n");\
  if(val1 == val2){\
    __CUnitTest_logAssertNotEqualError(__FILE__, __FUNCTION__, __LINE__, val1, val2);\
  } else {\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0)

/*
 * \brief Assert that strings are equal
*/
#define CUnitTest_assertStrEqual(str1, str2)do{\
  printNote("Testing CUnitTest_assertStrEqual("#str1", "#str2")...\n");\
  if(strcmp(str1, str2)){\
    __CUnitTest_logAssertStrEqualError(__FILE__, __FUNCTION__, __LINE__, str1, str2);\
  } else{\
    printOK("Assertion" BOLD " ok\n" RESET);\
  }\
}while(0);


void __CUnitTest_logAssertError(const char* file, const char* func, const int line, const char* assertion);

void __CUnitTest_logAssertEqualError(const char* file, const char* func,
                                   const int line, const int val1, const int val2);

void __CUnitTest_logAssertNotEqualError(const char* file, const char* func,
                                   const int line, const int val1, const int val2);

void __CUnitTest_logAssertStrEqualError(const char* file, const char* func,
                                   const int line, const char* str1, const char* str2);


void __CUnitTest_addTestFunc(const char* test_set_name,
                                     test_func funcptr, const char* func_name);

void __CUnitTest_registerFailure(const char* info_str);

#endif
